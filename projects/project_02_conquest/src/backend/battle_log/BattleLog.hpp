// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cinttypes>
#include <cstdio>
#include <string>
#include <vector>

#include "ActionLog.hpp"
#include "DamageLog.hpp"

#define OUTPUT_FOLDER "battleLogs"
#define BATTLE_LOG_RECORD_FILE ".BattleLogRecord.tsv"
#define FILE_EXTENSION ".tsv"
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
  int setBattleLog(const char &recordMode,
    const std::string& battleLogFolder = OUTPUT_FOLDER);

  /**
   * @brief Records an action into the battle log.
   * @param action, The ActionLog object containing action details.
   */
  void recordAction(ActionLog &action);

  /**
   * @brief Records the header for statistics in the battle log.
   * @param recordTitle title of the simulation or game.
   * @param elementCount The number of elements in the data structure.
   * @param actionsCount The number of actions performed.
   */
  void recordStatsHeader(std::string recordTitle, int elementCount = 0
    , int actionsCount = 0);

  /// @brief Records the statistics of the actions performed in a battle log tsv
  /// @param actions Vector of actions of the same type to be recorded.
  /// @param printResponsible
  void recordStats(std::vector<ActionLog>& actions
    , bool printResponsible = false);

  /// @brief Records the statistics of the actions performed in a battle log tsv
  /// @param actions Vector of damageActions of the same type to be recorded.
  /// @param printResponsible
  void recordStats(std::vector<DamageLog>& actions
    , bool printResponsible = false);


  /**
   * @brief Destructor that closes the battle log file.
   */
  ~BattleLog();

 private:
  FILE* battleLogFile;  ///< File pointer for the battle log file.
  /// @brief Folder where battle logs are stored
  /// Working directory + battleLogs/ as default.
  std::string battleLogFolder;
  std::string battleLogName;  /// Name of the battle log file.
  std::string logRecordPath;  ///< Path to the battle log record file.

  /**
   * @brief Sets the battle log file name based on the record mode.
   * @param recordMode The mode of the log ('G' for game, 'S' for simulation).
   * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
   */
  int setBattleLogName(const char &recordMode);
};
