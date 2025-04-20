// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include "UISlot.hpp"

#define BOARD_ROWS 6
#define BOARD_COLS 16
#define SLOT_DIMENSION 100
#define NO_COORDINATES -1

#define PLAYER_1 1
#define PLAYER_2 2

#define X_OFFSET 85
#define Y_OFFSET 125

#define SLOT_MASKS_TYPES 3

const std::string SLOT_MASK_FOLDER = "assets/sprites/slotMasks/";
const std::string LIGHT_MASKS_PATH = "light/";
const std::string DARK_MASKS_PATH = "dark/";
const std::string SLOT_MASKS[SLOT_MASKS_TYPES] = {"unaccessed.png", "hit.png"
    , "flagged.png"};

#define SHOW_RESET true  // Indicates if the slot should be unflagged
enum SlotState {
  UNACCESSED,
  HIT,
  FLAGGED,
};

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
  void activateBoard();
  void deactivateBoard();
  void resetSelection(int player);
  Coordinates* getCoordinates(int player);

  void setHitMaskAt(int row, int col);
  void setFlaggedMaskAt(int row, int col);
  void resetMaskAt(int row, int col, bool showReset);
  void maskOpponentSlots(int player);

 private:
  UISlot*** board;
  Fl_Color light_cell;
  Fl_Color dark_cell;
  Coordinates* player1SelectedSlot = nullptr;
  Coordinates* player2SelectedSlot = nullptr;
  Fl_PNG_Image* slotMasks[6];

  void initSlotMasks();
  void setBoard(int startX, int startY);
  void setSlotCallback(int row, int col);
  bool isValid(int row, int col) const;
  SlotState getSlotState(int row, int col, SlotState state) const;
};
