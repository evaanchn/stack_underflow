// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

#include "Board.hpp"
#include "BattleLog.hpp"

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
  /// @brief sends an attack to a certain slot
  /// @param attackerRow row of the attacker
  /// @param attackerCol col of the attacker
  /// @param victimRow row of the victim
  /// @param victimCol col of the victim
  /// @return the result of the attack
  size_t attackVessel(int attackerRow, int attackerCol, int victimRow,
      int victimCol);

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

  /// @brief returns the winner's identifier
  size_t getWinner();

  /// @brief constructor method of the class
  Game();
  /// @brief destructor method of the class
  ~Game();

  /**
   * @brief checks if the game is over
   * @return true is game is over
   */
  bool isGameOver();

  /**
   * @brief checks out if a slot in the board is available
   * @return true or false
   */
  bool isSlotOccupied(int row, int col);

  /// @brief moves vessel from one slot to another
  void moveVessel(int fromRow, int fromCol, int toRow, int toCol);

  /// @brief Upgrades selected vessel
  /// @param row selected row
  /// @param col selected column
  /// @return true if the vessel was upgraded, false otherwise
  bool upgradeVessel(int row, int col);

  /// @brief Sets new turn to false, indicating the new turn has been noted
  void resetNewTurn();

  /**
   * @brief saves a vessels in the specified coordinates
   * @param row selected row
   * @param col selected column
   * @param vesselID kind of vessel for being saved
   */
  void setVesselAt(int row, int col, int64_t vesselID);

  /// @brief checks if new turn happened
  /// @return true if new turn happened
  bool switchedTurns();

  /**
   * @brief validades if a player has the capacity to save more vessels
   * @return true or false
   */
  bool validateVesselWeight();

 private:
  std::map<size_t, Player> players;
  bool gameOver;
  size_t winner;
  size_t currentPlayer;
  bool newTurn;
  BattleLog* battleLog;
  Board* board;

  void setPlayers();
};
