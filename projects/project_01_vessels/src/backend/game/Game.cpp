// Copyright 2025 stack_underflow CC-BY 4.0

#include "Game.hpp"

Game::Game()
  : currentPlayer(PLAYER1)
  , winner(0)
  , newTurn(true) {
  setPlayers();
  board = new Board();
  battleLog = new BattleLog(RECORD_GAME);
}

void Game::setPlayers(){
  Player player1;
  Player player2;
  players[PLAYER1] = player1;
  players[PLAYER2] = player2;

  // Set players with initial values
  for (auto player : &players) {
    player.actions = 3;
    player.purchasePoints = 30;
    player.totalVesselWeight = 0;
    player.upgradePoints = 0;
  }
}

Game::~Game() {
  delete this->battleLog();
  delete this->board;
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
    players[currentPlayer] = 3;
    if (currentPlayer == PLAYER1) {
      currentPlayer = PLAYER2;
    } else {
      currentPlayer = PLAYER1;
    }
  }
}

int64_t Game::getCurrentPlayer() {
  return currentPlayer;
}

bool Game::isSlotOccupied(int64_t row, int64_t col) {
  // TODO(Andrey): Validade slots
  // return boad[row][col].isOccupied;
}

void Game::setVesselAt(int64_t row, int64_t col, int64_t vesselID) {
  vector<ActionLog> logs;
  std::vector<int64_t> coodinates;
  coodinates.push_back(row);
  coodinates.push_back(col);
  if (insertVessel(coordinates, vesselID, currentPlayer, &logs)) {
    printf("Vessel inserted succesfully");
  } else {
    printf("Error: couldn't insert the vessel");
  }
  for (auto log : &logs) {
    recordAction(log);
  }
}

bool Game::validadeVesselWeight() {
  size_t vesselWeight = players[currentPlayer].totalVesselWeight;
  if (vesselWeight == 0 || vesselWeight == MAX_VESSEL_WEIGHT) {
    return false;
  } else {
    return true;
  }
}
