// Copyright 2025 stack_underflow CC-BY 4.0

#include "Game.hpp"

Game::Game() : galaxy(nullptr), player({0, 0}), gameOver(false) {
  // create the battle log
  this->battleLog = new BattleLog();
  if (!this->battleLog) {
    throw std::runtime_error("BattleLog instance could not be created.");
  }
}

void Game::startGame(const char* galaxyFileDirectory) {
  // avoid memory leaks if called multiple times
  if (this->galaxy) {
    delete this->galaxy;
    this->galaxy = nullptr;
  }
  this->galaxy = new Galaxy(galaxyFileDirectory);
  if (!this->galaxy) {
    throw std::runtime_error("Galaxy instance could not be created.");
  }
}

Game::~Game() {
  if (this->galaxy) delete this->galaxy;
  this->galaxy = nullptr;
  if (this->battleLog) delete this->battleLog;
  this->battleLog = nullptr;
}

void Game::probe(size_t vesselID, Coordinates& startPlanet) {
  (void)startPlanet;  // Suppress unused variable warning
  // SolarSystem* currentSolarSystem = this->galaxy->getCurrentSolarSystem();
  // transform the startPlanet coordinates to a Node<Planet*> pointer
  // Check if the vesselID is valid
  if (vesselID == SPACE_VESSEL_TYPE::BFS_VESSEL) {
    // this->battleLog->recordAction(this->vessels.bfs.probe();)
  } else if (vesselID == SPACE_VESSEL_TYPE::DFS_VESSEL){
    // this->battleLog->recordAction(this->vessels.dfs.probe();)
  }
}

void Game::scout(size_t vesselID, Coordinates& startPlanet) {
  (void)startPlanet;  // Suppress unused variable warning
  // SolarSystem* currentSolarSystem = this->galaxy->getCurrentSolarSystem();
  // transform the startPlanet coordinates to a Node<Planet*> pointer
  // Check if the vesselID is valid
  if (vesselID == SPACE_VESSEL_TYPE::DIJKSTRA_VESSEL) {
    // this->battleLog->recordAction(this->vessels.dijkstra.scout(startPlanet));
  } else if (vesselID == SPACE_VESSEL_TYPE::FLOYD_VESSEL){
    // this->battleLog->recordAction(this->vessels.floyd.scout(startPlanet));
  }
}

size_t Game::attack(size_t vesselID, Coordinates& startPlanet
    , Coordinates& targetPlanet) {
  (void)startPlanet;  // Suppress unused variable warning
  (void)targetPlanet;  // Suppress unused variable warning
  // SolarSystem* currentSolarSystem = this->galaxy->getCurrentSolarSystem();
  // transform the startPlanet coordinates to a Node<Planet*> pointer
  // transform the targetPlanet coordinates to a Node<Planet*> pointer
  // Check if the vesselID is valid
  if (vesselID == SPACE_VESSEL_TYPE::GREEDY_VESSEL) {
    // this->battleLog->recordAction(this->vessels.exhaustiveSearch
      // .attack(startPlanet, targetPlanet));
  } else if (vesselID == SPACE_VESSEL_TYPE::LOCAL_SEARCH_VESSEL){
    // this->battleLog->recordAction(this->vessels.localSearch
      //  .attack(startPlanet, targetPlanet));
  } else if (vesselID == SPACE_VESSEL_TYPE::EXHAUSTIVE_SEARCH_VESSEL){
    // this->battleLog->recordAction(this->vessels.exhaustiveSearch
      // .attack(startPlanet, targetPlanet));
  } else if (vesselID == SPACE_VESSEL_TYPE::EXHAUSTIVE_PRUNE_VESSEL){
    // this->battleLog->recordAction(this->vessels.exhaustiveSearchPrune
      // .attack(startPlanet, targetPlanet);));
  }
  // recieve the attack result into the the targetPlanet and update boss status
  return 0; // Placeholder return value, replace with actual attack result
}

void Game::collectPurchasePoints() {
  // Collect purchase points based on active mines
  if (this->player.purchasePoints < MAX_PURCHASE_POINTS) {
    this->player.purchasePoints 
      += this->player.activeMines * PURCHASE_POINTS_INC;
  }
}

bool Game::consumePurchasePoints(size_t points) {
  if (this->player.purchasePoints >= points) {
    this->player.purchasePoints -= points;
    return true;
  }
  return false;
}

bool Game::isGameOver() {
  return this->gameOver;
}

Galaxy* Game::getGalaxy() const {
  return this->galaxy;
}
BattleLog* Game::getBattleLog() const {
  return this->battleLog;
}
VesselsCollection<Planet*, size_t>& Game::getVessels() {
  return this->vessels;
}

size_t Game::getPurchasePoints() {
  return this->player.purchasePoints;
}