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

  /**
  * @brief Obtain access to slots
  * 
  * @param coordinates A vector containing the row and column indices.
  * @param playerID The ID of the player requesting access.
  * @return Slot* Pointer to the Slot, or nullptr if invalid.
  */
  Slot* getSlot(std::vector<int> coordinates, int playerID);

  /**
  * @brief Obtain pointer to the Vessel on a slot
  * 
  * @param coordinates A vector containing the row and column indices.
  * @param playerID The ID of the player requesting the vessel.
  * @return Vessel* Pointer to the Vessel, or nullptr if no vessel exists.
  */
  Vessel* getVessel(std::vector<int> coordinates, int playerID);

  /**
  * @brief Inserts a Vessel into a specific Slot on the Board.
  * 
  * @param coordinates A vector containing the row and column indices.
  * @param vesselID The ID/type of Vessel to insert.
  * @param playerID The ID of the player performing the insertion.
  * @return true if insertion was successful, false otherwise.
  */
  bool insertVessel(std::vector<int> coordinates, int vesselID, int playerID
    , std::vector<ActionLog>& logs);

  /**
  * @brief Checks if a slot is occupied by a Vessel.
  * 
  * @param coordinates A vector containing the row and column indices.
  * @return true if occupied, false if free
  */
  bool isSlotOccupied(std::vector<int> coordinates);

  /**
  * @brief Moves a Vessel from an origin Slot to a destination Slot.
  * 
  * @param origin A vector containing the origin row and column indices.
  * @param destination destination row and column indices.
  * @param playerID The ID of the player performing the move.
  * @return true if move was successful, false otherwise.
  */
  bool moveVessel(std::vector<int> origin, std::vector<int> destination
    , int playerID);

  /**
  * @brief Deletes a Vessel at the specified coordinates.
  * 
  * @param coordinates A vector containing the row and column indices.
  * @param playerID The ID of the player performing the deletion.
  * @return true if deletion was successful, false otherwise.
  */
  bool deleteVessel(std::vector<int> coordinates, int playerID);

  /**
  * @brief Checks if a slot coordinates are invalid for a player or out of
  * bounds.
  * 
  * @param coordinates A vector containing the row and column indices.
  * @param playerID The ID of the player.
  * @return true if the Slot is invalid, false otherwise.
  */
  bool invalidSlot(std::vector<int> coordinates, int playerID);

  /// @brief Get the information of a Vessel at a specific position
  /// @param row The row index of the Slot.
  /// @param col The column index of the Slot.
  /// @return Vessel information, or "Empty slot" if not any
  std::string getVesselInfoAt(int row, int col) const;

 private:
  /**
  * @brief Creates and allocates a matrix of Slots.
  * 
  * @param rows Number of rows.
  * @param columns Number of columns.
  * @return Slot** Pointer to the created Slot matrix.
  */
  static Slot** createSlotsMatrix(const int rows, const int columns);

  /**
  * @brief Destroys a matrix of Slots and deallocates memory.
  * 
  * @param matrix The Slot matrix to destroy.
  * @param rows Number of rows.
  */
  static void destroySlotsMatrix(Slot** matrix, int rows);

  /**
  * @brief Deletes all Vessels present on the Board.
  */
  void deleteVessels();

  /**
  * @brief Factory method to create a Vessel object based on an ID.
  * 
  * @param vesselID The ID/type of Vessel to create.
  * @return Vessel* Pointer to the newly created Vessel.
  */
  Vessel* vesselFactory(int vesselID);

 private:
  Slot** slots;  ///< 2D array of Slots representing the game board.
};
