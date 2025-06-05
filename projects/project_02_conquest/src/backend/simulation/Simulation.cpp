// Copyright 2025 stack_underflow CC-BY 4.0

#include <iostream>

#include "Random.hpp"
#include "Simulation.hpp"

Simulation::Simulation()
: game(nullptr)
, battleLog(nullptr)
, galaxyCSVPath("")
, operationsNumber(0)
, outputFolder(OUTPUT_FOLDER)
, linkProbability(LINK_PROB) {
}

Simulation::~Simulation() {
  delete this->game;
  this->game = nullptr;
  delete this->battleLog;
  this->battleLog = nullptr;
}


bool Simulation::analyzeArguments(int argc, char* argv[]) {
  // look for help argument
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }
  if (argc < 3) {
    return false;
  }
  // required arguments
  this->galaxyCSVPath = argv[1];
  try {
    this->operationsNumber = std::stoul(argv[2]);
  } catch(const std::invalid_argument& error) {
    std::cerr << "Warning: " << error.what()
      << std::endl << usage;
    return false;
  }
  // optional arguments
  if (argc >= 4) this->outputFolder = argv[3];
  if (argc >= 5) {
    try {
      this->linkProbability = std::stod(argv[4]);
    } catch(const std::invalid_argument& error) {
      std::cerr << "Warning: " << error.what() << std::endl << usage;
      return false;
    }
  }
  // valid values range check
  return (operationsNumber > 0 && linkProbability > 0.0);
}

int Simulation::run(int argc, char* argv[]) {
  // Analyze given arguments
  if (!this->analyzeArguments(argc, argv)) {
    return EXIT_FAILURE;
  }
  // Initialize simulation objects
  try {
    this->initSimulation();
  }
  catch(const std::exception& initError) {
    std::cerr << initError.what() << '\n';
    return EXIT_FAILURE;
  }
  // Run the tests
  this->test();
  return EXIT_SUCCESS;
}

void Simulation::initSimulation() {
  this->game = new Game();
  if (!this->game) {
    throw std::runtime_error("Game instance could not be created.");
  }
  this->game->startGame(this->galaxyCSVPath.c_str());
  if (this->game->getBattleLog()->setBattleLog(RECORD_SIMULATION
      , this->outputFolder) != EXIT_SUCCESS) {
    throw std::runtime_error("BattleLog instance could not be created.");
  }
}

void Simulation::test() {
  // first solar system
  if (!this->game->getGalaxy()->createCurrentSolarSystem()) return;
  // Loop through all solar systems in the galaxy completing them
  do {
    SolarSystem* solarSystem = this->game->getGalaxy()->getCurrentSolarSystem();
    // If solar system is not available, skip to the next one
    if (!solarSystem) {
      std::cerr << "Simulation: Skipping invalid solar system" << std::endl;
      continue;
    }
    // perform the tests for the current solar system until is complete
    this->completeSystemTest();
  } while (this->game->getGalaxy()->passNextSolarSystem());
}

void Simulation::completeSystemTest() {
  // Prepare the action logs
  std::vector<ActionLog> BFSLogs;
  std::vector<ActionLog> DFSLogs;
  std::vector<ActionLog> DijkstraLogs;
  std::vector<ActionLog> FloydLogs;
  std::vector<DamageLog> GreedyLogs;
  std::vector<DamageLog> LocalSearchLogs;
  std::vector<DamageLog> ExhaustiveSearchLogs;
  std::vector<DamageLog> exhaustiveSearchPruneLogs;
  size_t actionsCount = 0;
  // Perform random actions until the solar system is complete
  while (!this->game->getGalaxy()->getCurrentSolarSystem()->isComplete()) {
    int actionType = Random<int>().generateRandomInRange(0
      , TOTAL_VESSELS);
    switch (actionType) {
      case BFS_VESSEL:
        BFSLogs.push_back(this->tesProbingVessel
          (&this->game->getVessels().bfs));
        break;
      case DFS_VESSEL:
        DFSLogs.push_back(this->tesProbingVessel
          (&this->game->getVessels().dfs));
        break;
      case DIJKSTRA_VESSEL:
        DijkstraLogs.push_back(this->tesScoutingVessel
          (&this->game->getVessels().dijkstra));
        break;
      case FLOYD_VESSEL:
        FloydLogs.push_back(this->tesScoutingVessel
          (&this->game->getVessels().floyd));
        break;
      case GREEDY_VESSEL:
        GreedyLogs.push_back(this->testAttackVessel
          (&this->game->getVessels().greedySearch));
        break;
      case LOCAL_SEARCH_VESSEL:
      LocalSearchLogs.push_back(this->testAttackVessel
          (&this->game->getVessels().localSearch));
        break;
      case EXHAUSTIVE_SEARCH_VESSEL:
        ExhaustiveSearchLogs.push_back(this->testAttackVessel
          (&this->game->getVessels().exhaustiveSearch));
        break;
      case EXHAUSTIVE_PRUNE_VESSEL:
        exhaustiveSearchPruneLogs.push_back(this->testAttackVessel
          (&this->game->getVessels().exhaustiveSearchPrune));
        break;
      default:
        // do nothing
        break;
    }
    ++actionsCount;
  }
  // Log the results of the tests
  this->game->getBattleLog()->recordStatsHeader(this->game->getGalaxy()->
    getCurrentSolarSystem()->getName(), this->game->getGalaxy()->
    getCurrentSolarSystem()->getPlanetsCount(), actionsCount);
  this->game->getBattleLog()->recordStats(BFSLogs, true);
  this->game->getBattleLog()->recordStats(DFSLogs);
  this->game->getBattleLog()->recordStats(DijkstraLogs, true);
  this->game->getBattleLog()->recordStats(FloydLogs);
  this->game->getBattleLog()->recordStats(GreedyLogs, true);
  this->game->getBattleLog()->recordStats(LocalSearchLogs);
  this->game->getBattleLog()->recordStats(ExhaustiveSearchLogs);
  this->game->getBattleLog()->recordStats(exhaustiveSearchPruneLogs);
}

ActionLog Simulation::tesProbingVessel(ProbingVessel<Planet*, size_t>* vessel) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  // Perform probe from the first node in the solar system graph
  return vessel->probe(startingNode, system->getGraph()->getAdjacencyList()
      , system->getExploredPlanets(), PROBE_LIMIT);
}

ActionLog Simulation::tesScoutingVessel
    (ScoutingVessel<Planet*, size_t>* vessel) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  // Perform pathing from the first node in the solar system graph
  return vessel->scout(system->getGraph(), system->getExploredPlanets()
    , system->getRevealedPaths(), startingNode);
}

DamageLog Simulation::testAttackVessel(AttackVessel<Planet*, size_t>* vessel) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  if (system->isComplete()) return DamageLog("NA");
  size_t attackWeight = 0;
  size_t targetIndex = 0;
  // Select the first planet with a boss to attack
  for (size_t index = 0; targetIndex < system->getGraph()->getNodes().size()
      ; ++index) {
    // Ensure the target has a boss
    if (system->getGraph()->getNodes()[index]->getData()->hasBoss()) {
      targetIndex = index;
      break;
    }
  }
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  Node<Planet*>* targetNode = system->getGraph()->getNodes()[targetIndex];
  // Performs attack from the first node in the solar system graph
  DamageLog log = vessel->attack(startingNode, targetNode
      , system->getGraph()->getAdjacencyList()
      , system->getGraph()->getNodeIndexes(), system->getRevealedPaths()
      , attackWeight);
  // Take the damage from the attack
  if (attackWeight > 0) {
    // only base points of damage for simulation purposes
    system->getGraph()->getNodes()[targetIndex]->getData()
    ->getBoss()->receiveDamage(MAX_DAMAGE_SIMULATION /*/ attackWeight*/);
    // Update the boss alive status
    system->updateBossAlive(system->getGraph()->getNodes()
      [targetIndex]->getData());
  }
  return log;
}
