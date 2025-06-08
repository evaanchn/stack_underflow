// Copyright 2025 stack_underflow CC-BY 4.0

#include "Game.hpp"

Game::Game() : galaxy(nullptr), player({0, 0}), gameOver(false) {
  // create the battle log
  this->battleLog = new BattleLog();
  if (!this->battleLog) {
    throw std::runtime_error("BattleLog instance could not be created.");
  }
}

bool Game::startGame(const char* galaxyFileDirectory) {
  // avoid memory leaks if called multiple times
  if (this->galaxy) {
    delete this->galaxy;
    this->galaxy = nullptr;
  }
  try {
    this->galaxy = new Galaxy(galaxyFileDirectory);
    if (!this->galaxy) {
      throw std::runtime_error("Galaxy instance could not be created.");
    }
    if (!this->galaxy->createCurrentSolarSystem()) {
      throw std::runtime_error("Initial Solar System could not be created.");
    }
  } catch(const CSVException& e) {
    std::cerr << e.what() << '\n';
    return false;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << '\n';
    return false;
  }
  this->player = {0, 1};  // Reset player data
  this->gameOver = false;  // Reset game over status
  return true;
}

Game::~Game() {
  if (this->galaxy) delete this->galaxy;
  this->galaxy = nullptr;
  if (this->battleLog) delete this->battleLog;
  this->battleLog = nullptr;
}

bool Game::probe(int vesselID, int startPlanetIndex, ActionLog& probeLog) {
  if (!this->consumeEtherium(VESSELS_COSTS[vesselID])) return false;
  SolarSystem* system = this->galaxy->getCurrentSolarSystem();
  // start planet node
  assert(startPlanetIndex >= 0 || startPlanetIndex <
      (int)system->getPlanetsCount());  // Invalid planet index
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [startPlanetIndex];
  // Check if the vessel ID is valid
  assert(vesselID >= BFS_VESSEL || vesselID <= DFS_VESSEL);
  // Choose probing vessel
  probeLog = vessels.probingVessels.at(vesselID - BFS_VESSEL)->probe
    (startingNode, system->getGraph()->getAdjacencyList()
    , system->getExploredPlanets(), PROBE_LIMIT);
  this->battleLog->recordAction(probeLog);
  return true;
}

bool Game::probe(int vesselID, int startPlanetIndex) {
  ActionLog probeLog;
  return this->probe(vesselID, startPlanetIndex, probeLog);
}

bool Game::scout(int vesselID, int startPlanetIndex, ActionLog& scoutLog) {
  // Consume etherium for scouting
  if (!this->consumeEtherium(VESSELS_COSTS[vesselID])) return false;
  SolarSystem* system = this->galaxy->getCurrentSolarSystem();
  assert(startPlanetIndex >= 0 || startPlanetIndex <
    (int)system->getPlanetsCount());  // Invalid planet index
  // start planet node
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [startPlanetIndex];
  // Check if the vessel ID is valid
  assert(vesselID >= DIJKSTRA_VESSEL || vesselID <= FLOYD_VESSEL);
  scoutLog = vessels.scoutingVessels.at(vesselID - DIJKSTRA_VESSEL)
    ->scout(system->getGraph(), system->getExploredPlanets()
    , system->getRevealedPaths(), startingNode);
  this->battleLog->recordAction(scoutLog);
  return true;
}

bool Game::scout(int vesselID, int startPlanetIndex) {
  ActionLog scoutLog;
  return this->scout(vesselID, startPlanetIndex, scoutLog);
}

int Game::attack(int vesselID, int targetPlanetIndex, DamageLog attackLog) {
  // Consume etherium for attacking
  if (!this->consumeEtherium(VESSELS_COSTS[vesselID]))
    return INSUFICIENT_ETHERIUM;
  SolarSystem* system = this->galaxy->getCurrentSolarSystem();
  // Validate target planet index
  assert(targetPlanetIndex >= 0 || targetPlanetIndex <
      (int)system->getPlanetsCount());
  Node<Planet*>* targetNode = system->getGraph()->getNodes()
    [targetPlanetIndex];
  // Ensure the target has a boss
  if (!targetNode->getData()->hasBoss()) {
    return HAS_NO_BOSS;  // Target planet does not have a boss
  }
  // start at entry planet
  Node<Planet*>* startingNode = system->getGraph()->getNodes()
    [system->getPlanetsIndexes()[system->getEntryPlanet()]];
  size_t attackWeight = 0;
  // Check if the vessel ID is valid
  assert(vesselID >= GREEDY_VESSEL || vesselID <= EXHAUSTIVE_PRUNE_VESSEL);
  // Choose scouting vessel and attack
  AttackVessel<Planet*, size_t>* attackVessel = this->vessels.attackVessels.at
    (vesselID - GREEDY_VESSEL);
  attackLog = attackVessel->attack(startingNode, targetNode
      , system->getGraph()->getAdjacencyList()
      , system->getGraph()->getNodeIndexes(), system->getRevealedPaths()
      , attackWeight);
  // Record the attack action
  this->battleLog->recordAction(attackLog);
  return this->damageAction(attackWeight, targetPlanetIndex);
}

int Game::damageAction(const size_t attackWeight, int targetPlanetIndex) {
  SolarSystem* system = this->galaxy->getCurrentSolarSystem();
  assert(system);
  int damage = 0;
  if (attackWeight > 0) {
    size_t planetCount = this->galaxy->getCurrentSolarSystem()
      ->getPlanetsCount();
    Planet* planet = system->getGraph()->getNodes()[targetPlanetIndex]
      ->getData();
    // damage calculation
    planet->getBoss()->receiveDamage( damage = (BOSS_INIT_HEALTH * planetCount)
      / attackWeight);
    // Update the boss alive status and add a mine if dead
    if(!system->updateBossAlive(planet)) {
      ++this->player.activeMines;
    }
  }
  return damage;
}

int Game::attack(int vesselID, int targetPlanetIndex) {
  DamageLog attackLog;
  return this->attack(vesselID, targetPlanetIndex, attackLog);
}

void Game::collectEtherium() {
  // Collect purchase points based on active mines
  if (this->player.etherium < MAX_ETHERIUM) {
    this->player.etherium
      += this->player.activeMines * ETHERIUM_INC;
  }
}

bool Game::consumeEtherium(size_t points) {
  if (this->player.etherium >= points) {
    this->player.etherium -= points;
    return true;
  }
  return false;
}

bool Game::isCurrentSolarSystemCompleted() const {
  return this->galaxy->getCurrentSolarSystem()->isComplete();
}

bool Game::passNextSolarSystem() {
  if (this->galaxy->passNextSolarSystem()) {
    this->player.activeMines = 1;  // Reset active mines for the new system
    this->player.etherium = 0;  // Reset etherium for the new system
    return true;
  }
  this->gameOver = true;
  return false;
}

bool Game::isGameOver() const {
  return this->gameOver;
}

Galaxy* Game::getGalaxy() const {
  return this->galaxy;
}

std::vector<Planet*> Game::getCurrentPlanets() {
  assert(this->galaxy);
  return this->galaxy->getCurrentSolarSystem()->getPlanets();
}

std::unordered_set<Planet *>& Game::getCurrentExplored() {
  return this->galaxy->getCurrentSolarSystem()->getExploredPlanets();
}

std::vector<std::vector<bool>>& Game::getCurrentPaths() {
  return this->galaxy->getCurrentSolarSystem()->getRevealedPaths();
}

Graph<Planet *, size_t>* Game::getCurrentGraph() {
  return this->galaxy->getCurrentSolarSystem()->getGraph();
}

size_t Game::getSystemsLeftCount() const {
  if (this->galaxy) {
    return this->galaxy->getSystemsLeftCount();
  }
  return 0;
}

BattleLog* Game::getBattleLog() const {
  return this->battleLog;
}
VesselsCollection<Planet*, size_t>& Game::getVessels() {
  return this->vessels;
}

size_t Game::getVesselsCount() const {
  return this->vessels.vesselsCount;
}

size_t Game::getCurrentRemainingBosses() const {
  if (!this->galaxy) return 0;
  return this->galaxy->getCurrentSolarSystem()->getBossesAlive();
}

size_t Game::getCurrentMInes() const {
  return this->player.activeMines;
}

size_t Game::getCurrentEtherium() const {
  return this->player.etherium;
}
