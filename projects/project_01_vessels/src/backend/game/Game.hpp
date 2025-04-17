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

#define TOTAL_VESSELS 6

struct Player {
  size_t actions;
  size_t purchasePoints;
  size_t upgradePoints;
  size_t totalVesselWeight;
};

class Game {
 public:
  void attackVessel(int64_t attackerRow, int64_t attackerCol, int64_t victimRow,
      int64_t victimCol);

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
  /// @brief destructor method of the class
  ~Game();

  /**
   * @brief checks out if a slot in the board is available
   * @return true or false
   */
  bool isSlotOccupied(int64_t row, int64_t col);

  /// @brief Sets new turn to false, indicating the new turn has been noted
  void resetNewTurn();

  /**
   * @brief saves a vessels in the specified coordinates
   * @param row selected row
   * @param col selected column
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
  bool newTurn;
  BattleLog* battlelog;
  Board* board;

  void setPlayers();
};
