// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <iostream>
#include <string>

class Vessel {
 public:
  // Constructor
  Vessel(std::string nameInit, int64_t healthInit, size_t costInit
      , size_t weightInit);

  /**
   * @brief Decrease the health value of the vessel with a valid amount of
   * damage
   * 
   * @param damageDealT
   */
  void takeDamage(int64_t damageDealt);

  /**
   * @brief Checks the health to be above 0
   * 
   * @return true: health <= 0
   * @return false: health > 0 
   */
  bool isAlive();

 protected:
  std::string name;
  int64_t health = 0;
  size_t cost = 0;
  size_t weight = 0;
};
