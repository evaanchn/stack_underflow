// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <ctime>

class ActionLog {
 public:
  /**
   * @brief Constructs an ActionLog object for one action
   * @param action, the action being recorded (insertion, elimination, search)
   */
  explicit ActionLog(const std::string action = " ");

  /**
   * @brief Sets the name of the responsible algorithm
   * @param responsible, The name of the algorithm
   */
  void setResponsible(const std::string responsible);

  /**
   * @brief Sets the action name.
   * @param action, The name of the operation being recorded
   */
  void setAction(const std::string action);

  /**
   * @brief Records the start time of the action.
   */
  void recordStart();

  /**
   * @brief Records the end time of the action and stores iteration count.
   * @param iterations The number of iterations performed.
   */
  void recordEnd(size_t iterations);

  /**
   * @brief Get record iterations
   * 
   * @return size_t
   */
  size_t getIterations();

  /**
   * @brief Get record time
   * 
   * @return double
   */
  double getDurationTime();

  /**
   * @brief Converts the logged action details to a string representation.
   * @return A formatted string containing the action details.
   */
  std::string toString();

 private:
  std::string responsible;  ///< The alogrithm responsible for the action.
  std::string action;  ///< The action being logged.
  size_t iterations;  ///< Number of iterations performed
  timespec startTime;  ///< The start time of the action.
  timespec endTime;  ///< The end time of the action.

  /**
   * @brief Computes and returns the duration of the action.
   * @return A string representation of the elapsed time, in ms.
   */
  std::string getDuration();
};
