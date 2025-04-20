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

class Simulation {
 public:
  Simulation();
  ~Simulation() { delete battleLog; }
  void simulate();

 private:
  BattleLog* battleLog;
  Vessel** vessels;

  void testInsertion(Vessel* vessel);
  void testSearch(Vessel* vessel);
  void testElimination(Vessel* vessel);
  void printTestStats(std::string action, std::vector<ActionLog>& logs);
};
