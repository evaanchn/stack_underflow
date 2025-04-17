// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <vector>

#include "Vessel.hpp"

class Slot {
 public:
  // Constructor
  Slot();
  // Disable copy and move
  Slot(const Slot& other) = delete;
  Slot(Slot&& other) = delete;
  Slot& operator=(const Slot& other) = delete;
  Slot& operator=(Slot&& other) = delete;

  ~Slot();

  /**
   * @brief Validate empty slot
   * 
   * @return true 
   * @return false 
   */
  bool isOccupied();

  /**
   * @brief Get vessel inside
   * 
   * @return const Vessel*
   * @return nullptr: if empty
   */
  Vessel* getVessel();

  /**
   * @brief Try to insert a vessel on its coordinates
   * 
   * @param newVessel pointer to a valid vessel
   * @return true success
   * @return false failure
   */
  bool insertVessel(Vessel* newVessel);

  /**
   * @brief Vessel is no longer on this slot
   * 
   * @return true success
   * @return false failure
   */
  bool removeVessel();

  /**
   * @brief Vessel is destroyed
   * 
   * @return true success
   * @return false failure
   */
  bool destroyVessel();

 private:
  std::vector<int> coordinates;
  bool occupied;
  Vessel* vessel;
};
