#include "UIBoard.hpp"
#include <iostream>

UIBoard::UIBoard(int startX, int startY) {
  grid = new UISlot**[BOARD_ROWS];
  player1SelectedSlot = new Coordinates{NO_COORDINATES, NO_COORDINATES};
  player2SelectedSlot = new Coordinates{NO_COORDINATES, NO_COORDINATES};
  this->setBoard(startX, startY);
}

UIBoard::~UIBoard() {
  delete player2SelectedSlot;
  delete player1SelectedSlot;
  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = 0; j < BOARD_COLS; ++j) delete grid[i][j];
    delete[] grid[i];
  }
  delete[] grid;
}

void UIBoard::setBoard(int startX, int startY) {
  for (int row = 0; row < BOARD_ROWS; ++row) {
    grid[row] = new UISlot*[BOARD_COLS];
    for (int col = 0; col < BOARD_COLS; ++col) {
      int x = startX + col * SLOT_DIMENSION;
      int y = startY + row * SLOT_DIMENSION;

      grid[row][col] = new UISlot(x, y);

      // To draw cells in checkerboard pattern
      Fl_Color color = ((row + col) % 2 == 0) ? LIGHT_CELL : DARK_CELL;
      grid[row][col]->setColor(color);

      // Set coordinate callback
      setSlotCallback(row, col);
    }
  }
}

void UIBoard::setSlotCallback(int row, int col) {
  if (isValid(row, col)) {
    grid[row][col]->setOnClick([this, row, col]() {
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
    grid[row][col]->setVessel(vessel);
  }
}

void UIBoard::removeVesselAt(int row, int col) {
  if (isValid(row, col)) grid[row][col]->clearVessel();
}


void UIBoard::moveVessel(int fromRow, int fromCol, int toRow, int toCol) {
  if (isValid(fromRow, fromCol) && isValid(toRow, toCol)) {
    Fl_PNG_Image* temp = grid[fromRow][fromCol]->getVessel();
    grid[fromRow][fromCol]->clearVessel();
    grid[toRow][toCol]->setVessel(temp);
  }
}

void UIBoard::deactivateHalf(bool leftSide) {
  int startCol = leftSide ? 0 : BOARD_COLS / 2;
  int endCol = leftSide ? BOARD_COLS / 2 : BOARD_COLS;
  for (int i = 0; i < BOARD_ROWS; ++i) {
    for (int j = startCol; j < endCol; ++j) {
      grid[i][j]->deactivate();
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
