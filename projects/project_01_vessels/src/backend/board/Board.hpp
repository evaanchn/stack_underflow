// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <iostream>
#include <vector>

// board size
#define BOARD_ROWS 6
#define BOARD_COLUMNS 16
// last column that belongs to the first player
#define LIMIT_COL 7

// player IDs
#define PLAYER1 1
#define PLAYER2 2

// vessels ID
#define HASHSET 0
#define REDBLACK 1
#define BINARYSEARCH 2
#define BTREE 3
#define SPLAYTREE 4
#define LINEARSEARCH 5

#include "Slot.hpp"

class Board {
 public:
  // Constructor
  Board();
  // Disable copy and move
  Board(const Board& other) = delete;
  Board(Board&& other) = delete;
  Board& operator=(const Board& other) = delete;
  Board& operator=(Board&& other) = delete;
  ~Board();

  Slot* getSlot(std::vector<int> coordinates, int8_t playerID);
  Vessel* getVessel(std::vector<int> coordinates, int8_t playerID);
  bool insertVessel(std::vector<int> coordinates, int8_t vesselID
    , int8_t playerID);
  bool moveVessel(std::vector<int> origin, std::vector<int> destination
    , int8_t playerID);
  bool deleteVessel(std::vector<int> coordinates, int8_t playerID);

 private:
  bool invalidSlot(std::vector<int> coordinates, int8_t playerID);
  static Slot** createSlotsMatrix(const int rows, const int columns);
  static void destroySlotsMatrix(Slot** matrix, int rows);
  Vessel* vesselFactory(int8_t vesselID);

 private:
  Slot** slots;  // [BOARD_ROWS][BOARD_COLUMNS];
};
