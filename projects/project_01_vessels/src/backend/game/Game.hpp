// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstddef>
#include <cstdint>

// player IDs
#define PLAYER1 1
#define PLAYER2 2

struct Player {
  size_t purchasePoints;
  size_t upgradePoints;
  size_t totalVesselWeight;
};

class Game {
 public:
  /**
   * @brief pendiente ...
   * @return true or false
   */
  bool validadeVesselWeight();

  /**
   * @brief pendiente ...
   * @return
   */
  int64_t getCurrentPlayer();

  /**
   * @brief pendiente
   */
  void setVesselAt(int64_t, int64_t col, int64_t vesselType);

  /**
   * @brief pendiente
   * @return true or false
   */
  bool isSlotOccupied(int64_t row, int64_t col);

  /**
   * @brief pendiente
   * @return true if current player can buy specified vessel based on vessels 
     weight and money
   */
  bool canBuyVessel(int64_t vesselType);

 private:
  bool gameOver;
  int64_t winner;
  int64_t currentPlayer;
};
