// Copyright 2025 stack_underflow CC-BY 4.0

#include <exception>

#include "Board.hpp"

Board::Board(): slots(nullptr) {
  this->slots = createSlotsMatrix(BOARD_ROWS, BOARD_COLUMNS);
  if (this->slots == nullptr) {
    throw std::bad_alloc();
  }
}

Board::~Board() {
  deleteVessels();
  destroySlotsMatrix(this->slots, BOARD_ROWS);
}

bool Board::invalidSlot(std::vector<int> coordinates, int playerID) {
  // check index out of bounds
  if (coordinates.size() != 2 ||
      coordinates.at(0) >= BOARD_ROWS || coordinates.at(1) >= BOARD_COLUMNS) {
    std::cerr << "Index out of bounds\n";
    return true;
  }
  // check valid coordinates for a player
  if ((playerID == PLAYER1) && coordinates.at(1) > LIMIT_COL) return true;
  if ((playerID == PLAYER2) && coordinates.at(1) <= LIMIT_COL) return true;
  // else
  return false;
}

Slot* Board::getSlot(std::vector<int> coordinates, int playerID) {
  if (invalidSlot(coordinates, playerID)) {
    return nullptr;
  }
  return &this->slots[coordinates.at(0)][coordinates.at(1)];
}

Vessel* Board::getVessel(std::vector<int> coordinates, int playerID) {
  if (invalidSlot(coordinates, playerID)) {
    return nullptr;
  }
  return this->slots[coordinates.at(0)][coordinates.at(1)].getVessel();
}

bool Board::insertVessel(std::vector<int> coordinates, int vesselID
    , int playerID) {
  bool insert_success = false;
  if (invalidSlot(coordinates, playerID)) return false;
  Vessel* vessel = vesselFactory(vesselID);
  if (vessel == nullptr) return false;
  if (this->getSlot(coordinates, playerID)->insertVessel(vessel)) return true;
  // if it could not be inserted, delete memory allocated
  delete vessel;
  return false;
}

bool Board::moveVessel(std::vector<int> origin, std::vector<int> destination
    , int playerID) {
  // valid source and destination
  if (this->invalidSlot(origin, playerID)
      || this->invalidSlot(destination, playerID)) {
    return false;
  }
  // move
  if (!this->getSlot(destination, playerID)
      ->insertVessel(this->getSlot(origin, playerID)->getVessel())) {
    return false;
  }
  this->getSlot(origin, playerID)->removeVessel();
  return true;
}

bool Board::deleteVessel(std::vector<int> coordinates, int playerID) {
  if (this->invalidSlot(coordinates, playerID)) return false;
  return this->getSlot(coordinates, playerID)->destroyVessel();
}

Slot** Board::createSlotsMatrix(const int rows, const int columns) {
  Slot** matrix = (Slot**)calloc(rows, sizeof(Slot*));
  if (matrix) {
    for (int row = 0; row < rows; ++row) {
      if ((matrix[row] = (Slot*)calloc(columns, sizeof(Slot))) == NULL) {
        destroySlotsMatrix(matrix, rows);
        return NULL;
      }
    }
  }
  return matrix;
}

void Board::destroySlotsMatrix(Slot** matrix, int rows) {
  if (matrix) {
    for (int row = 0; row < rows; ++row) {
      free(matrix[row]);
    }
    free(matrix);
  }
}

void Board::deleteVessels() {
  for (int row = 0; row < BOARD_ROWS; ++row) {
    for (int column = 0; column < BOARD_COLUMNS; ++column) {
      this->slots[row][column].~Slot();
    }
  }
}

#include "HashsetVessel.hpp"
#include "RedBlackTreeVessel.hpp"
#include "BinarySearchVessel.hpp"
#include "BTreeVessel.hpp"
#include "SplayTreeVessel.hpp"
#include "LinearSearchVessel.hpp"

Vessel* Board::vesselFactory(int vesselID) {
  if (vesselID == HASHSET) return new HashsetVessel();
  if (vesselID == REDBLACK) return new RedBlackTreeVessel();
  if (vesselID == BINARYSEARCH) return new BinarySearchVessel();
  if (vesselID == BTREE) return new BTreeVessel();
  if (vesselID == SPLAYTREE) return new SplayTreeVessel();
  if (vesselID == LINEARSEARCH) return new LinearSearchVessel();
  return nullptr;
}

