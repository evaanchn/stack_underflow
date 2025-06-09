// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "ActionLog.hpp"
#include <unordered_map>

class DamageLog : public ActionLog {
 private:
  size_t damage;  ///< The amount of damage recorded.

 public:
  /**
   * @brief Constructs a DamageLog object for recording damage actions.
   * @param action, the action being recorded (e.g., "damage", "repair").
   */
  explicit DamageLog(const std::string action = " ");

  /**
   * @brief Sets the damage amount.
   * @param damage, The amount of damage to be recorded.
   */
  void setDamage(size_t damage);

  /**
   * @brief Gets the recorded damage amount.
   * @return size_t The amount of damage recorded
   */
  size_t getDamage() const;

  /**
   * @brief Converts the logged damage action details to a string representation.
   * @return A formatted string containing the action details and damage amount.
   */
  std::string toString() override;

  /**
   * @brief Calculates the aritmetic mean from the iterations of a given logs
   * array
   * @warning the sum of all iterations must be lower than 2^64
   * 
   * @param logs 
   * @return int64_t
   */
  static uint64_t iterationsMean(std::vector<DamageLog>& logs);

  /**
   * @brief Calculates the aritmetic mean from the duration of a given logs
   * array
   * @warning the sum of all iterations must be lower than long double max value
   * 
   * @param logs 
   * @return long double 
   */
  static long double durationMean(std::vector<DamageLog>& logs);

  /**
   * @brief Calculates the aritmetic mean of the damages recorded in logs
   * 
   * @param logs array of logs
   * @return uint64_t Mean
   */
  static uint64_t damageMean(std::vector<DamageLog>& logs);

  /**
   * @brief Calculates the mode of the recorded damages in a logs array
   * 
   * @param logs array of damage logs
   * @return uint64_t Mode
   */
  static uint64_t damageMode(std::vector<DamageLog>& logs);
};
