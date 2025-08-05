// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include "UISlot.hpp"

#define BOARD_ROWS 6
#define BOARD_COLS 16
#define SLOT_DIMENSION 67
#define NO_COORDINATES -1

#define PLAYER_1 1
#define PLAYER_2 2

#define X_OFFSET 57
#define Y_OFFSET 83

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
  /**
   * @brief Constructs a UIBoard instance and initializes the board grid.
   * @param startX The starting X-coordinate for the top-left slot
   * (default is X_OFFSET).
   * @param startY The starting Y-coordinate for the top-left slot
   * (default is Y_OFFSET).
   */
  explicit UIBoard(int startX = X_OFFSET, int startY = Y_OFFSET);

  /**
   * @brief Destroys the UIBoard instance and deallocates all resources.
   */
  ~UIBoard();

  /**
   * @brief Places a vessel image at the specified board cell.
   * @param row The row index.
   * @param col The column index.
   * @param vessel Pointer to the image representing the vessel.
   */
  void setVesselAt(int row, int col, Fl_PNG_Image* vessel);

  /**
   * @brief Removes the vessel from the specified cell.
   * @param row The row index.
   * @param col The column index.
   */
  void removeVesselAt(int row, int col);

  /**
   * @brief Moves a vessel from one cell to another.
   * @param fromRow The source row.
   * @param fromCol The source column.
   * @param toRow The destination row.
   * @param toCol The destination column.
   */
  void moveVessel(int fromRow, int fromCol, int toRow, int toCol);

  /**
   * @brief Enables interaction with all slots on the board.
   */
  void activateBoard();

  /**
   * @brief Disables interaction with all slots on the board.
   */
  void deactivateBoard();

  /**
   * @brief Clears the selected slot coordinates for the specified player.
   * @param player The player index (PLAYER_1 or PLAYER_2).
   */
  void resetSelection(int player);

  /**
   * @brief Gets the currently selected slot coordinates for the given player.
   * @param player The player index (PLAYER_1 or PLAYER_2).
   * @return Pointer to the Coordinates structure.
   */
  Coordinates* getCoordinates(int player);

  /**
   * @brief Applies a "hit" mask on the specified slot.
   * @param row The row index.
   * @param col The column index.
   */
  void setHitMaskAt(int row, int col);

  /**
   * @brief Applies a "flagged" mask on the specified slot.
   * @param row The row index.
   * @param col The column index.
   */
  void setFlaggedMaskAt(int row, int col);

  /**
   * @brief Resets the slot mask to its default state.
   * @param row The row index.
   * @param col The column index.
   * @param showReset Whether to show the mask after reset or hide it.
   */
  void resetMaskAt(int row, int col, bool showReset);

  /**
   * @brief Masks all opponent slots so they are hidden from the current player.
   * @param player The current player index (PLAYER_1 or PLAYER_2).
   */
  void maskOpponentSlots(int player);

 private:
  /**
   * @brief 2D array representing the board grid of UISlots.
   */
  UISlot*** board;

  /**
   * @brief FLTK color used for light-colored board cells.
   */
  Fl_Color light_cell;

  /**
   * @brief FLTK color used for dark-colored board cells.
   */
  Fl_Color dark_cell;

  /**
   * @brief Pointer to the slot selected by Player 1.
   */
  Coordinates* player1SelectedSlot;

  /**
   * @brief Pointer to the slot selected by Player 2.
   */
  Coordinates* player2SelectedSlot;

  /**
   * @brief Array of preloaded slot mask images (both light and dark versions).
   */
  Fl_PNG_Image* slotMasks[6];

  /**
   * @brief Loads the images for all slot mask states.
   */
  void initSlotMasks();

  /**
   * @brief Initializes the board layout and populates it with UISlots.
   * @param startX The X-coordinate for the top-left cell.
   * @param startY The Y-coordinate for the top-left cell.
   */
  void setBoard(int startX, int startY);

  /**
   * @brief Assigns a click callback to a slot to track selection by player.
   * @param row The slot's row index.
   * @param col The slot's column index.
   */
  void setSlotCallback(int row, int col);

  /**
   * @brief Checks whether the given coordinates are within board bounds.
   * @param row The row index.
   * @param col The column index.
   * @return True if valid, false otherwise.
   */
  bool isValid(int row, int col) const;

  /**
   * @brief Determines the appropriate slot mask state based on cell color.
   * @param row The row index.
   * @param col The column index.
   * @param state The desired SlotState (e.g., HIT, FLAGGED).
   * @return The adjusted SlotState (light or dark).
   */
  SlotState getSlotState(int row, int col, SlotState state) const;
};
