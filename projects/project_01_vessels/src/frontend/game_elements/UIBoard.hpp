// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <vector>
#include "UISlot.hpp"

#define BOARD_ROWS 6
#define BOARD_COLS 16
#define SLOT_DIMENSION 100
#define NO_COORDINATES -1

#define PLAYER_1 1
#define PLAYER_2 2

#define X_OFFSET 85
#define Y_OFFSET 130

struct Coordinates {
  int row;
  int col;
};

class UIBoard {
 public:
  explicit UIBoard(int startX = X_OFFSET, int startY = Y_OFFSET);
  ~UIBoard();

  void setVesselAt(int row, int col, Fl_PNG_Image* vessel);
  void removeVesselAt(int row, int col);
  void moveVessel(int fromRow, int fromCol, int toRow, int toCol);
  void deactivateHalf(bool leftSide);
  void resetSelection(int player);
  Coordinates* getCoordinates(int player);

 private:
  UISlot*** grid;
  Fl_Color light_cell;
  Fl_Color dark_cell;
  Coordinates* player1SelectedSlot = nullptr;
  Coordinates* player2SelectedSlot = nullptr;

  void setBoard(int startX, int startY);
  void setSlotCallback(int row, int col);
  bool isValid(int row, int col) const;
};
