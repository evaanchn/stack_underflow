// Copyright 2025 stack_underflow CC-BY 4.0

#include <iostream>

#include "Random.hpp"
#include "Simulation.hpp"

Simulation::Simulation()
: game(nullptr)
, galaxyCSVPath("")
, outputFolder(OUTPUT_FOLDER)
, recordActions(!RECORD_ACTIONS) {
  battleLog = new BattleLog();
}

Simulation::~Simulation() {
  if (this->game) delete this->game;
  this->game = nullptr;
  if (this->battleLog) delete this->battleLog;
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

  if (argc >= 2) this->galaxyCSVPath = argv[1];
  else return false;

  // optional arguments
  if (argc >= 3) {
    std::string thirdArg = argv[2];
    if (thirdArg.find("print") != std::string::npos)
        this->recordActions = RECORD_ACTIONS; 
  }
  if (argc >= 4) this->outputFolder = argv[3];
  return true;
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
  if (!this->game->startGame(this->galaxyCSVPath.c_str())) {
    throw std::runtime_error("Galaxy instance could not be created.");
  }
  if (this->battleLog->setBattleLog(RECORD_SIMULATION
      , this->outputFolder) != EXIT_SUCCESS) {
    throw std::runtime_error("BattleLog instance could not be created.");
  }
}

void Simulation::test() {
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
  std::vector<ActionLog> dijkstraLogs;
  std::vector<ActionLog> floydLogs;
  std::vector<DamageLog> greedyLogs;
  std::vector<DamageLog> localSearchLogs;
  std::vector<DamageLog> exhaustiveSearchLogs;
  std::vector<DamageLog> exhaustiveSearchPruneLogs;
  std::unordered_set<std::string> attacksPerformed = {};

  // Start with initial probe and scout to continue game
  this->testProbe(BFSLogs, DFSLogs);
  this->testScout(dijkstraLogs, floydLogs);
  size_t actionsCount = 2;
  SolarSystem* currentSystem = this->game->getGalaxy()->getCurrentSolarSystem();
  int startingAction = PROBE;  // First of available actions is probing
  // Perform random actions until the solar system is complete
  while (!this->game->getGalaxy()->getCurrentSolarSystem()->isComplete()) {
    int actionType = Random<int>().generateRandomInRange(startingAction
        , ATTACK);
    if (actionType == PROBE) {
      this->testProbe(BFSLogs, DFSLogs);
      // If all planets have been discovered, discard PROBE as an option
      if (currentSystem->getExploredPlanets().size()
         == currentSystem->getPlanetsCount()) {
        startingAction = SCOUT;
      }
    }
    else if (actionType == SCOUT) {
      this->testScout(dijkstraLogs, floydLogs);
      // Set the only available action to attack, now that paths are revealed
      if (currentSystem->getExploredPlanets().size()
         == currentSystem->getPlanetsCount()) {
        startingAction = ATTACK;
      }
    }
    else if (actionType == ATTACK) {
      this->testAttack(greedyLogs, localSearchLogs
        , exhaustiveSearchLogs, exhaustiveSearchPruneLogs, attacksPerformed);
    }
    ++actionsCount;
  }

  // Log the results of the tests
  this->battleLog->recordStatsHeader(this->game->getGalaxy()->
    getCurrentSolarSystem()->getName(), this->game->getGalaxy()->
    getCurrentSolarSystem()->getPlanetsCount(), actionsCount);
  this->battleLog->recordStats(BFSLogs, true);
  this->battleLog->recordStats(DFSLogs);
  this->battleLog->recordStats(dijkstraLogs, true);
  this->battleLog->recordStats(floydLogs);
  this->battleLog->recordStats(greedyLogs, true);
  this->battleLog->recordStats(localSearchLogs);
  this->battleLog->recordStats(exhaustiveSearchLogs);
  this->battleLog->recordStats(exhaustiveSearchPruneLogs);
}

void Simulation::testProbe(std::vector<ActionLog>& BFSLogs
      , std::vector<ActionLog>& DFSLogs) {
  int vesselType = Random<int>().generateBinaryRandom(0, 1);
  if (vesselType == 0) {
    BFSLogs.push_back(this->tesProbingVessel
        (&this->game->getVessels().bfs));
  } else {
    DFSLogs.push_back(this->tesProbingVessel
        (&this->game->getVessels().dfs));
  }
}

void Simulation::testScout(std::vector<ActionLog>& dijkstraLogs
      , std::vector<ActionLog>& floydLogs) {
  int vesselType = Random<int>().generateBinaryRandom(0, 1);
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  if (system->getExploredPlanets().size() == system->getPlanetsCount()) 
      vesselType = 1;
  if (vesselType == 0) {
    dijkstraLogs.push_back(this->tesScoutingVessel
        (&this->game->getVessels().dijkstra));
  } else {
    floydLogs.push_back(this->tesScoutingVessel
        (&this->game->getVessels().floyd));
  }
}

void Simulation::testAttack(std::vector<DamageLog>& greedyLogs
      , std::vector<DamageLog>& localSearchLogs
      , std::vector<DamageLog>& exhaustiveSearchLogs
      , std::vector<DamageLog>& exhaustiveSearchPruneLogs
      , std::unordered_set<std::string>& attacksPerformed) {
  if (attacksPerformed.size() == ATTACKS_AVAILABLE) attacksPerformed.clear();
  int vesselType = GREEDY;
  do {
    vesselType = Random<int>().generateRandomInRange(GREEDY, PRUNED);
  } while (attacksPerformed.find(ATTACKS_IDS[vesselType])
      != attacksPerformed.end());
  attacksPerformed.insert(ATTACKS_IDS[vesselType]);

  if (vesselType == GREEDY) {
    greedyLogs.push_back(this->testAttackVessel
        (&this->game->getVessels().greedySearch, GREEDY));
  } else if (vesselType == LOCAL) {
    localSearchLogs.push_back(this->testAttackVessel
        (&this->game->getVessels().localSearch, LOCAL));
  } else if (vesselType == EXHAUSTIVE) {
    exhaustiveSearchLogs.push_back(this->testAttackVessel
        (&this->game->getVessels().exhaustiveSearch, EXHAUSTIVE));
  } else if (vesselType == PRUNED) {
    exhaustiveSearchPruneLogs.push_back(this->testAttackVessel
        (&this->game->getVessels().exhaustiveSearchPrune, PRUNED));
  }
}

ActionLog Simulation::tesProbingVessel(ProbingVessel<Planet*, size_t>* vessel) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  // Perform probe from the first node in the solar system graph
  ActionLog log = vessel->probe(startingNode
      , system->getGraph()->getAdjacencyList()
      , system->getExploredPlanets(), PROBE_LIMIT);
  if (this->recordActions) this->battleLog->recordAction(log);
  return log;
}

ActionLog Simulation::tesScoutingVessel(ScoutingVessel<Planet*
    , size_t>* vessel) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  // Perform pathing from the first node in the solar system graph
  ActionLog log =  vessel->scout(system->getGraph()
    , system->getExploredPlanets()
    , system->getRevealedPaths(), startingNode);
  if (this->recordActions) this->battleLog->recordAction(log);
  return log;
}

DamageLog Simulation::testAttackVessel(AttackVessel<Planet*, size_t>* vessel
    , int type) {
  SolarSystem* system = this->game->getGalaxy()->getCurrentSolarSystem();
  if (system->isComplete()) return DamageLog("NA");
  size_t attackWeight = 0;
  int targetIndex = -1;
  std::unordered_set<Planet*> explored = system->getExploredPlanets();
  // Find an explored planet with boss
  for (auto* planet : explored) {
    if (planet->hasBoss()) {
      targetIndex = system->getPlanetsIndexes()[planet];
    }
  }
  // If no boss in sight yet
  if (targetIndex == -1) return DamageLog(ATTACKS_IDS[type]);

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
    int attack = 500 / attackWeight < MIN_DAMAGE_SIMULATION ?
        MIN_DAMAGE_SIMULATION :  500 / attackWeight ;
    // only base points of damage for simulation purposes
    system->getGraph()->getNodes()[targetIndex]->getData()
    ->getBoss()->receiveDamage(attack);
    // Update the boss alive status
    system->updateBossAlive(system->getGraph()->getNodes()
      [targetIndex]->getData());
  }
  if (this->recordActions) this->battleLog->recordAction(log);

  return log;
}
