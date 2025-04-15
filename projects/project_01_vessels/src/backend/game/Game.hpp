// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

#include "Board.hpp"
#include "BattleLog.hpp"
#inclide "ActionLog.hpp";

// player IDs
#define PLAYER1 1
#define PLAYER2 2
#define MAX_VESSEL_WEIGHT 10

struct Player {
  size_t purchasePoints;
  size_t upgradePoints;
  size_t totalVesselWeight;
  size_t actions;
};

class Game {
 public:
  /**
   * @brief pendiente
   * @return true if current player can buy specified vessel based on vessels 
     weight and money
   */
  bool canBuyVessel(int64_t vesselID);

  /**
   * @brief validades if a player has more actions in a round
   */
  void consumeAction();

  /**
   * @brief report who is the player that has the turn in the round
   * @return current player
   */
  size_t getCurrentPlayer();

  /// @brief constructor method of the class
  Game();

  /**
   * @brief checks out if a slot in the board is available
   * @return true or false
   */
  bool isSlotOccupied(int64_t row, int64_t col);

  /**
   * @brief saves a vessels in the specified coordinates
   * @param row selected row
   * @param row selected column
   * @param vesselID kind of vessel for being saved
   */
  void setVesselAt(int64_t row, int64_t col, int64_t vesselID);

  /**
   * @brief validades if a player has the capacity to save more vessels
   * @return true or false
   */
  bool validadeVesselWeight();

 private:
  map<size_t, Player> players;
  bool gameOver;
  int64_t winner;
  size_t currentPlayer;
  BattleLog battlelog;
  Board board;
};
