// Copyright 2025 stack_underflow CC-BY 4.0

#include "Game.hpp"

Game::Game()
  : gameOver(false) 
  , winner(0)
  , currentPlayer(PLAYER1) 
  , newTurn(true) 
  , battleLog(nullptr)
  , board(nullptr) {
  setPlayers();
  this->battleLog = new BattleLog();
  this->battleLog->setBattleLog(RECORD_GAME);
  this->board = new Board();
}

void Game::setPlayers() {
  Player player1;
  Player player2;
  players[PLAYER1] = player1;
  players[PLAYER2] = player2;

  // Set players with initial values
  for (auto &player : players) {
    player.second.actions = 3;
    player.second.purchasePoints = 30;
    player.second.totalVesselWeight = 0;
    player.second.upgradePoints = 0;
  }
}

Game::~Game() {
  delete this->battleLog;
  delete this->board;
}

size_t Game::attackVessel(int attackerRow, int attackerCol, int victimRow,
  int victimCol) {
  Vessel* attacker = this->board->getVessel({attackerRow, attackerCol}
      , currentPlayer);
  ActionLog log = ActionLog();
  size_t damage = attacker->calculateDamage(log);
  this->battleLog->recordAction(log);
  // If there was an opponent vessel there, deal damage
  if (this->board->isSlotOccupied({victimRow, victimCol})) {
    size_t opponent = (currentPlayer + 1) % 2;
    Vessel* victim = this->board->getVessel({victimRow, victimCol}, opponent);
    if (victim != nullptr) {
      victim->takeDamage(damage);
      if (!victim->isAlive()) {
        players[opponent].totalVesselWeight -= victim->getWeight();
        this->board->deleteVessel({victimRow, victimCol}, opponent);
        // Check for loss
        if (players[opponent].totalVesselWeight == 0) {
          winner = currentPlayer;
          gameOver = true;
        }
      }
    }
  } else {
    // If the slot is empty, the attack is not wasted
    // but the damage is not applied
    players[currentPlayer].upgradePoints += damage / 2;
  }
  return damage;
}

bool Game::canBuyVessel(int64_t vesselID) {
  const size_t weights[TOTAL_VESSELS] = {5, 3, 2, 2, 2, 1};
  const size_t costs[TOTAL_VESSELS] = {200, 150, 80, 50, 30, 1};
  size_t vesselWeight = players[currentPlayer].totalVesselWeight;
  size_t money = players[currentPlayer].purchasePoints;
  if (vesselWeight >= weights[vesselID] && money >= costs[vesselID]) {
    return true;
  } else {
    return false;
  }
}

void Game::consumeAction() {
  --players[currentPlayer].actions;
  if (players[currentPlayer].actions == 0) {
    newTurn = true;
    players[currentPlayer].actions = 3;
    // Switch player
    ++currentPlayer;
    currentPlayer %= 2;
  }
}

size_t Game::getCurrentPlayer() {
  return currentPlayer;
}

size_t Game::getWinner() {
  return winner;
}

bool Game::isGameOver() {
  return gameOver;
}

bool Game::isSlotOccupied(int row, int col) {
  return this->board->isSlotOccupied({row, col});
}

void Game::moveVessel(int fromRow, int fromCol, int toRow, int toCol) {
  if (this->board->isSlotOccupied({fromRow, fromCol})
      && !this->board->isSlotOccupied({toRow, toCol})) {
    this->board->moveVessel({fromRow, fromCol}, {toRow, toCol}, currentPlayer);
  }
}

// upgrading a vessel -> deletion
bool Game::upgradeVessel(int row, int col) {
  Vessel* vessel = this->board->getVessel({row, col}, currentPlayer);
  if (vessel != nullptr) {
    if (vessel->maxedOut()) return false;
    std::vector<ActionLog> actionLogs;  // Since upgrade could be unsuccessful
    size_t upgradeIterations = vessel->upgradeVessel(
        players[currentPlayer].upgradePoints, actionLogs);
    for (auto &log : actionLogs) {
      this->battleLog->recordAction(log);
    }
    // If the iterations to upgrade are higher than the available
    // upgrade points, the vessel is not upgraded
    if (upgradeIterations > players[currentPlayer].upgradePoints) {
      players[currentPlayer].upgradePoints = 0;
      return false;
    } else {
      players[currentPlayer].upgradePoints -= upgradeIterations;
    }
  }
  return true;
}

void Game::resetNewTurn() {
  newTurn = false;
}

// Buying a vessel -> insertion
void Game::setVesselAt(int row, int col, int64_t vesselID) {
  std::vector<ActionLog> logs;
  std::vector<int> coordinates = {row, col};
  if (this->board->insertVessel(coordinates, vesselID, currentPlayer, logs)) {
    printf("Vessel inserted succesfully");
  } else {
    printf("Error: couldn't insert the vessel");
  }

  for (auto &log : logs) {
    this->battleLog->recordAction(log);
  }
}

bool Game::switchedTurns() {
  return newTurn;
}

bool Game::validateVesselWeight() {
  size_t vesselWeight = players[currentPlayer].totalVesselWeight;
  if (vesselWeight == 0 || vesselWeight == MAX_VESSEL_WEIGHT) {
    return false;
  } else {
    return true;
  }
}
