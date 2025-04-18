#include "UIBoard.hpp"

UIBoard::UIBoard(int startX, int startY) {
  board = new UISlot**[BOARD_ROWS];
  player1SelectedSlot = new Coordinates{NO_COORDINATES, NO_COORDINATES};
  player2SelectedSlot = new Coordinates{NO_COORDINATES, NO_COORDINATES};
  this->initSlotMasks();
  this->setBoard(startX, startY);
}

UIBoard::~UIBoard() {
  delete player2SelectedSlot;
  delete player1SelectedSlot;
  for (int i = 0; i < 2*SLOT_MASKS_TYPES; ++i) {
    delete slotMasks[i];
  }

  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = 0; j < BOARD_COLS; ++j) delete board[i][j];
    delete[] board[i];
  }
  delete[] board;
}

void UIBoard::initSlotMasks() {
  for (int i = 0; i < SLOT_MASKS_TYPES; ++i) {
    // Load light and dark slot masks
    std::string lightPath = SLOT_MASK_FOLDER + LIGHT_MASKS_PATH + SLOT_MASKS[i];
    slotMasks[i] = new Fl_PNG_Image(lightPath.c_str());

    std::string darkPath = SLOT_MASK_FOLDER + DARK_MASKS_PATH + SLOT_MASKS[i];
    slotMasks[i + 3] = new Fl_PNG_Image(darkPath.c_str());
  }
}

void UIBoard::setBoard(int startX, int startY) {
  for (int row = 0; row < BOARD_ROWS; ++row) {
    board[row] = new UISlot*[BOARD_COLS];
    for (int col = 0; col < BOARD_COLS; ++col) {
      int x = startX + col * SLOT_DIMENSION;
      int y = startY + row * SLOT_DIMENSION;

      board[row][col] = new UISlot(x, y);

      // To draw cells in checkerboard pattern
      Fl_Color color = ((row + col) % 2 == 0) ? LIGHT_CELL : DARK_CELL;
      Fl_PNG_Image* unaccessedMask = ((row + col) % 2 == 0) ?
          slotMasks[UNACCESSED]  // Light unaccessed mask
          : slotMasks[UNACCESSED + SLOT_MASKS_TYPES];  // Dark unaccessed mask
      board[row][col]->setColor(color);
      board[row][col]->setMask(unaccessedMask);

      // Set coordinate callback
      setSlotCallback(row, col);
    }
  }
}

void UIBoard::setSlotCallback(int row, int col) {
  if (isValid(row, col)) {
    board[row][col]->setOnClick([this, row, col]() {
      if (col >= 0 && col < BOARD_COLS / 2) {
        this->player1SelectedSlot->row = row;
        this->player1SelectedSlot->col = col;
      }
      else if (col >= BOARD_COLS / 2 && col < BOARD_COLS) {
        this->player2SelectedSlot->row = row;
        this->player2SelectedSlot->col = col;
      }
    });
  }
}

void UIBoard::setVesselAt(int row, int col, Fl_PNG_Image* vessel) {
  if (isValid(row, col) && vessel) {
    board[row][col]->setVessel(vessel);
  }
}

void UIBoard::removeVesselAt(int row, int col) {
  if (isValid(row, col)) board[row][col]->clearVessel();
}

void UIBoard::moveVessel(int fromRow, int fromCol, int toRow, int toCol) {
  if (isValid(fromRow, fromCol) && isValid(toRow, toCol)) {
    Fl_PNG_Image* temp = board[fromRow][fromCol]->getVessel();
    board[fromRow][fromCol]->clearVessel();
    board[toRow][toCol]->setVessel(temp);
  }
}

void UIBoard::deactivateHalf(bool leftSide) {
  int startCol = leftSide ? 0 : BOARD_COLS / 2;
  int endCol = leftSide ? BOARD_COLS / 2 : BOARD_COLS;
  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = startCol; j < endCol; ++j) {
      board[i][j]->deactivate();
    }
  }
}

bool UIBoard::isValid(int row, int col) const {
  return row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS;
}

void UIBoard::resetSelection(int player) {
  Coordinates* coordinates = player == PLAYER_1? 
      player1SelectedSlot : player2SelectedSlot;
  coordinates->row = coordinates->col = NO_COORDINATES;
}

Coordinates* UIBoard::getCoordinates(int player) {
  Coordinates* coordinates = player == PLAYER_1 ? 
      player1SelectedSlot : player2SelectedSlot;
  return coordinates;
}

void UIBoard::setHitMaskAt(int row, int col) {
  if (isValid(row, col)) {
    int hitMask = getSlotState(row, col, HIT);
    board[row][col]->setMask(slotMasks[hitMask]);
  }
}

void UIBoard::setFlaggedMaskAt(int row, int col) {
  if (isValid(row, col)) {
    int flaggedMask = getSlotState(row, col, FLAGGED);
    board[row][col]->setMask(slotMasks[flaggedMask]);
  }
}

void UIBoard::resetMaskAt(int row, int col) {
  if (isValid(row, col)) {
    int unaccessedMask = getSlotState(row, col, UNACCESSED);
    board[row][col]->setMask(slotMasks[unaccessedMask]);
  }
}

void UIBoard::maskOpponentSlots(int player) {
  for (int row = 0; row < BOARD_ROWS; ++row) {
    for (int col = 0; col < BOARD_COLS; ++col) {
      if (player == PLAYER_1 && col >= BOARD_COLS / 2) {
        board[row][col]->showMask();
      }
      else if (player == PLAYER_2 && col < BOARD_COLS / 2) {
        board[row][col]->showMask();
      }
      else {
        // Show my slots
        board[row][col]->hideMask();
      }
    }
  }
}

SlotState UIBoard::getSlotState(int row, int col, SlotState state) const {
  if ((row + col ) % 2 == 0) {
    return state;  // Light slot
  } else {
    return static_cast<SlotState>(state + SLOT_MASKS_TYPES);  // Dark slot
  }
}