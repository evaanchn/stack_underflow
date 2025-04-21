// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cinttypes>
#include <cstdio>
#include <string>
#include <vector>

#include "ActionLog.hpp"

#define BATTLE_LOG_RECORD_FILE "battleLogs/.BattleLogRecord.tsv"
#define RECORD_GAME 'G'
#define RECORD_SIMULATION 'S'

class BattleLog {
 public:
  /**
   * @brief Constructs a BattleLog object.
   */
  BattleLog() : battleLogFile(nullptr)
  , battleLogName() {}

  /**
   * @brief Sets up the battle log file based on the record mode.
   * @param recordMode The mode of the log ('G' for game, 'S' for simulation).
   * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
   */
  int setBattleLog(const char &recordMode);

  /**
   * @brief Records an action into the battle log.
   * @param action, The ActionLog object containing action details.
   */
  void recordAction(ActionLog &action);

  /**
   * @brief Records the header for statistics in the battle log.
   * @param elementCount, The number of elements in the data structure.
   * @param operationCount, The number of operations performed.
   */
  void recordStatsHeader(int elementCount, int operationCount);

  /// @brief Records the statistics of the actions performed in a battle log tsv
  /// @param actions Vector of actions of the same type to be recorded.
  /// @param actionType Type of operation to record.
  void recordStats(std::vector<ActionLog>& actions, std::string actionType);

  /**
   * @brief Destructor that closes the battle log file.
   */
  ~BattleLog();

 private:
  FILE* battleLogFile;  ///< File pointer for the battle log file.
  std::string battleLogName;  ///< Name of the battle log file.

  /**
   * @brief Sets the battle log file name based on the record mode.
   * @param recordMode The mode of the log ('G' for game, 'S' for simulation).
   * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
   */
  int setBattleLogName(const char &recordMode);
};
