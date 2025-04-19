// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <stdio.h>
#include <string>

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
