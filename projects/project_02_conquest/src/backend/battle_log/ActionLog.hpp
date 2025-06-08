// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <ctime>
#include <queue>
#include <string>
#include <vector>

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
   * @brief Get responsible name
   * 
   * @return std::string 
   */
  std::string getResponsible();

  /**
   * @brief Get action name
   * 
   * @return std::string 
   */
  std::string getAction();

  /**
   * @brief Converts the logged action details to a string representation.
   * @return A formatted string containing the action details.
   */
  virtual std::string toString();


  /// @brief Calculating the aritmetic mean from the iterations of ActionLog
  /// @param logs logs array
  /// @return resulting mean
  static uint64_t iterationsMean(std::vector<ActionLog>& logs);

  static long double durationMean(std::vector<ActionLog>& logs);

 protected:
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

/**
 * @brief Calculates the aritmetic mean from the iterations of a given logs
 * array
 * @warning the sum of all iterations must be lower than 2^64
 * 
 * @param logs 
 * @return int64_t 
 * @tparam LogType of the log entries in the vector
 */
template <typename LogType>
uint64_t iterationsMean(std::vector<LogType>& logs) {
  uint64_t sum = 0;
  uint64_t mean = 0;
  if (logs.empty()) return 0;
  for (auto &log : logs) {
    sum += log.getIterations();
  }
  mean = sum / logs.size();
  return mean;
}

/**
 * @brief Calculates the aritmetic mean from the duration of a given logs
 * array
 * @warning the sum of all iterations must be lower than long double max value
 * 
 * @param logs 
 * @return long double 
 * @tparam LogType of the log entries in the vector
 */
template <typename LogType>
long double durationMean(std::vector<LogType>& logs) {
  long double sum = 0.0L;
  long double mean = 0.0L;
  if (logs.empty()) return 0.0L;
  for (auto &log : logs) {
    sum += log.getDurationTime();
  }
  mean = sum / static_cast<long double>(logs.size());
  return mean;
}
