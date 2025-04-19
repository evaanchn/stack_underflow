// Copyright 2025 stack_underflow CC-BY 4.0

#include "Simulation.hpp"

Simulation::Simulation() {
  this->battleLog = new BattleLog();
  battleLog->setBattleLog(RECORD_SIMULATION);
  vessels = new Vessel*[VESSELS_TYPES];
  vessels[0] = new HashsetVessel();
  vessels[1] =  new RedBlackTreeVessel();
  vessels[2] =  new BinarySearchVessel();
  vessels[3] =  new BTreeVessel();
  vessels[4] = new SplayTreeVessel();
  vessels[5] =  new LinearSearchVessel();
}

void Simulation::simulate() {
  for (size_t i = 0; i < VESSELS_TYPES; ++i) {
    testInsertion(vessels[i]);
    testSearch(vessels[i]);
    testElimination(vessels[i]);
    delete vessels[i];
  }
  delete [] vessels;
}

void Simulation::testInsertion(Vessel* vessel) {
  std::vector<ActionLog> actionLogs;
  // initialize each action
  vessel->fillVessel(actionLogs);
  std::cout << "Success" << std::endl;
  // for (auto &log : actionLogs) {
  //   std::cout << log.toString() << std::endl;
  //   battleLog->recordAction(log);
  // }
  this->printTestStats("Insertion", actionLogs);
}

void Simulation::testSearch(Vessel* vessel) {
  std::vector<ActionLog> actionLogs;
  for (size_t i = 0; i < TESTS_AMOUNT; ++i) {
    ActionLog actionLog = ActionLog("Search");
    vessel->calculateDamage(actionLog);
    std::cout << actionLog.toString() << std::endl;
    // battleLog->recordAction(actionLog);
    actionLogs.push_back(actionLog);
  }
  printTestStats("Search", actionLogs);
}

void Simulation::testElimination(Vessel* vessel) {
  std::vector<ActionLog> eliminationLogs;
  for (size_t i = 0; i < TESTS_AMOUNT; ++i) {
    std::vector<ActionLog> actionLogs;
    vessel->upgradeVessel(ELEMENT_COUNT, actionLogs);
    // save logs
    for (auto &log : actionLogs) {
      std::cout << log.toString() << std::endl;
      // battleLog->recordAction(log);
    }
    eliminationLogs.push_back(actionLogs.front());
  }
  printTestStats("Elimination", eliminationLogs);
}

void Simulation::printTestStats(std::string action,
    std::vector<ActionLog>& logs) {
  std::cout << action << ": iterations mean = "
  << ActionLog::iterationsMean(logs) << " || ";
    std::cout << "duration mean = "<< ActionLog::durationMean(logs)
    << std::endl;
}
