// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <vector>

// TODO(Albin): discard when Vessel class is merged
#ifndef Vessel
typedef int Vessel;
#endif

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
   * @return true 
   * @return false 
   */
  bool insertVessel(Vessel* newVessel);

  /**
   * @brief Vessel is no longer on this slot
   * 
   */
  void removeVessel();

  /**
   * @brief Vessel is destroyed
   * 
   */
  void destroyVessel();

 private:
  std::vector<int> coordinates;
  bool occupied;
  Vessel* vessel;
};

