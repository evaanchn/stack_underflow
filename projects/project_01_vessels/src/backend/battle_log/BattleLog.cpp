// Copyright 2025 stack_underflow CC-BY 4.0

#include "BattleLog.hpp"

int BattleLog::setBattleLog(const char &recordMode) {
  int error = setBattleLogName(recordMode);
  if (error != EXIT_FAILURE) {
    this->battleLogFile = fopen(this->battleLogName.c_str(), "a+");
  }
  return error;
}

void BattleLog::recordAction(ActionLog &action) {
  fprintf(this->battleLogFile, "%s\n", action.toString().c_str());
}

void BattleLog::recordStatsHeader(int elementCount, int operationCount) {
  fprintf(this->battleLogFile,
    "<====================================>\n"
    "Aritmetic Mean\n"
    "- %d element insertions\n"
    "- %d search & delete operations\n", elementCount, operationCount);
}

void BattleLog::recordStats(std::vector<ActionLog>& actions
  , std::string actionType) {
  // only print responsible at insert (start)
  if (actionType == "insert") {
    fprintf(this->battleLogFile, "%s\titerations\tduration\n",
      actions.front().getResponsible().c_str());
  }
  fprintf(this->battleLogFile, "%s\t%" PRIu64
    "\t%Lg\n",
    actionType.c_str(),
    ActionLog::iterationsMean(actions),
    ActionLog::durationMean(actions));
}

BattleLog::~BattleLog() {
  if (battleLogFile) fclose(this->battleLogFile);
}

int BattleLog::setBattleLogName(const char &recordMode) {
  size_t gamesAmount = 0, simulationsAmount = 0;
  FILE* battleLogRecordFile = fopen(BATTLE_LOG_RECORD_FILE, "r");

  // If file record file does not exist yet, open with 'w' mode to create
  if (!battleLogRecordFile) {
    battleLogRecordFile = fopen(BATTLE_LOG_RECORD_FILE, "w");
  } else {
    // Make sure of successful read
    if (fscanf(battleLogRecordFile, "%*s\t%zu\t%*s\t%zu",
      &gamesAmount, &simulationsAmount) != 2) {
      printf("Failed to read battle log record file\n");
      return EXIT_FAILURE;
    }
  }

  // Add number to file name based on whether it is a game or simulation
  if (recordMode == RECORD_GAME) {
    this->battleLogName = "battleLogs/GameBattleLog#"
        + std::to_string(++gamesAmount) + ".txt";
  } else {
    this->battleLogName = "battleLogs/SimulationBattleLog#" +
        std::to_string(++simulationsAmount) + ".txt";
  }

  // Reopen to update numbers
  freopen(BATTLE_LOG_RECORD_FILE, "w", battleLogRecordFile);
  fprintf(battleLogRecordFile, "Games\t%zu\tSimulations\t%zu",
    gamesAmount, simulationsAmount);

  fclose(battleLogRecordFile);
  return EXIT_SUCCESS;
}
