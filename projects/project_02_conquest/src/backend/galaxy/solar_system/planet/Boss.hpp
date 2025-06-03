// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>

#define BOSS_INIT_HEALTH 50

class Boss {
 private:
  int healthPoints = BOSS_INIT_HEALTH;  ///< Current health points of the boss.

 public:
  /// @brief Default constructor initializing the boss with default health.
  Boss() { healthPoints = BOSS_INIT_HEALTH; }

  /**
   * @brief Applies damage to the boss, reducing its health.
   * @param damagePoints Amount of damage to apply.
   */
  void receiveDamage(int damagePoints);

  /**
   * @brief Retrieves the current health of the boss.
   * @return The boss's current health points.
   */
  int getHealth() const;

  /**
   * @brief Checks if the boss has been defeated.
   * @return True if the boss's health is zero or below, false otherwise.
   */
  bool isDead() const;

  /**
   * @brief Returns a string representation of the boss's status.
   * @return A std::string describing the boss.
   */
  std::string toString() const;
};
