// Copyright 2025 stack_underflow CC-BY 4.0

#include "BattleLog.hpp"

int BattleLog::setBattleLog(const char &recordMode,
    const std::string& battleLogFolder) {
  this->battleLogFolder = battleLogFolder;
  this->logRecordPath = this->battleLogFolder + "/" + BATTLE_LOG_RECORD_FILE;
  int error = setBattleLogName(recordMode);
  if (error != EXIT_FAILURE) {
    this->battleLogFile = fopen(this->battleLogName.c_str(), "a+");
  }
  return error;
}

void BattleLog::recordAction(ActionLog &action) {
  fprintf(this->battleLogFile, "%s\n", action.toString().c_str());
}

void BattleLog::recordAction(DamageLog &action) {
  fprintf(this->battleLogFile, "%s\n", action.toString().c_str());
}

void BattleLog::recordStatsHeader(std::string recordTitle, int elementCount
  , int actionsCount) {
  fprintf(this->battleLogFile,
    "//////////////////////////////////////////\n"
    "%s\n", recordTitle.c_str());
  if (elementCount > 0) {
    fprintf(this->battleLogFile, "- %d elements\n", elementCount);
  }
  if (actionsCount > 0) {
    fprintf(this->battleLogFile, "- %d actions\n", actionsCount);
  }
  fprintf(this->battleLogFile,
    "<====================================>\n"
    "Arithmetic Mean\n");
}

void BattleLog::recordStats(std::vector<ActionLog>& actions
    , bool printResponsible) {
  if (actions.empty()) {
    fprintf(this->battleLogFile, "Empty action log, nothing to record\n");
    return;
  }
  if (printResponsible) {
    fprintf(this->battleLogFile, "%s\titerations\tduration\n",
      actions.front().getResponsible().c_str());
  }
  fprintf(this->battleLogFile, "%s\t%" PRIu64
    "\t%Lg\n",
    actions.front().getAction().c_str(),
    ActionLog::iterationsMean(actions),
    ActionLog::durationMean(actions));
}

void BattleLog::recordStats(std::vector<DamageLog>& actions
    , bool printResponsible) {
  if (actions.empty()) {
    fprintf(this->battleLogFile, "Empty action log, nothing to record\n");
    return;
  }
  if (printResponsible) {
    fprintf(this->battleLogFile, "%s\titerations\tduration\tdamage\n",
      actions.front().getResponsible().c_str());
  }
  fprintf(this->battleLogFile, "%s\t%" PRIu64
    "\t%Lg\t%" PRIu64 "\n",
    actions.front().getAction().c_str(),
    DamageLog::iterationsMean(actions),
    DamageLog::durationMean(actions),
    DamageLog::damageMode(actions));
}

BattleLog::~BattleLog() {
  if (battleLogFile) fclose(this->battleLogFile);
}

int BattleLog::setBattleLogName(const char &recordMode) {
  size_t gamesAmount = 0, simulationsAmount = 0;
  FILE* battleLogRecordFile = fopen(logRecordPath.c_str(), "r");

  // If file record file does not exist yet, open with 'w' mode to create
  if (!battleLogRecordFile) {
    battleLogRecordFile = fopen(logRecordPath.c_str(), "w");
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
    this->battleLogName = this->battleLogFolder + "/GameBattleLog#"
        + std::to_string(++gamesAmount) + FILE_EXTENSION;
  } else {
    this->battleLogName = this->battleLogFolder + "/SimulationBattleLog#" +
        std::to_string(++simulationsAmount) + FILE_EXTENSION;
  }
  freopen(logRecordPath.c_str(), "w", battleLogRecordFile);
  fprintf(battleLogRecordFile, "Games\t%zu\tSimulations\t%zu",
    gamesAmount, simulationsAmount);

  fclose(battleLogRecordFile);
  return EXIT_SUCCESS;
}
