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
#define TESTS_AMOUNT 50

/**
 * @class Simulation
 * @brief Manages the simulation of various vessel operations and records performance statistics.
 */
class Simulation {
 public:
  /**
   * @brief Constructs a Simulation instance.
   *        Initializes the battle log and allocates different types of vessels.
   */
  Simulation();

  /// @brief Class destructor
  ~Simulation() { delete battleLog; }

  /**
   * @brief Runs the full simulation including insertion, search, and elimination tests
   *        on all vessel types, recording and printing the results.
   */
  void simulate();

 private:
  BattleLog* battleLog;
  Vessel** vessels;

  /**
   * @brief Prints the mean number of iterations and duration from a test log.
   * @param action The name of the test action (e.g., "Insertion", "Search").
   * @param logs Vector containing ActionLog entries for the test.
   */
  void printTestStats(std::string action, std::vector<ActionLog>& logs);
};