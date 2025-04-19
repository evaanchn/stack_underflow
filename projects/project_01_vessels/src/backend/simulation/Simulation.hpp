// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "BattleLog.hpp"
#include "HashsetVessel.hpp"
#include "RedBlackTreeVessel.hpp"
#include "BinarySearchVessel.hpp"
#include "BTreeVessel.hpp"
#include "SplayTreeVessel.hpp"
#include "LinearSearchVessel.hpp"

#define VESSELS_TYPES 6
#define TESTS_AMOUNT 30

class Simulation {
 public:
  Simulation();
  ~Simulation() { delete battleLog; }
  void simulate();

  /**
   * @brief Calculates the aritmetic mean from the iterations of a given logs
   * array
   * @warning the sum of all iterations must be lower than 2^64
   * 
   * @param logs 
   * @return int64_t 
   */
  u_int64_t iterationsMean(std::vector<ActionLog>& logs);

  /**
   * @brief Calculates the aritmetic mean from the duration of a given logs
   * array
   * @warning the sum of all iterations must be lower than long double max value
   * 
   * @param logs 
   * @return long double 
   */
  long double durationMean(std::vector<ActionLog>& logs);

 private:
  BattleLog* battleLog;
  Vessel** vessels;

  void testInsertion(Vessel* vessel);
  void testSearch(Vessel* vessel);
  void testElimination(Vessel* vessel);
  void printTestStats(std::string action, std::vector<ActionLog>& logs);
};
