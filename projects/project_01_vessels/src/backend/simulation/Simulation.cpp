// Copyright 2025 stack_underflow CC-BY 4.0

#include "Simulation.hpp"

Simulation::Simulation() {
#if 0
  BattleLog battleLog = BattleLog();
  battleLog.setBattleLog(RECORD_SIMULATION);

  vessels = new Vessels[VESSELS_TYPES];
  vessels[0] = new HashsetVessel();
  vessels[1] =  new RedBlackTreeVessel();
  vessels[2] =  new BinarySearchVessel();
  vessels[3] =  new BTreeVessel();
  vessels[4] = new SplayTreeVessel();
  vessels[5] =  new LinearSearchVessel();
#endif
}

void Simulation::simulate() {
  for (size_t i = 0; i < VESSELS_TYPES; ++i) {
    // testInsertion(vessels[i]);
    // testSearch(vessels[i]);
    // testElimination(vessels[i]);
    // delete vessels[i];
  }
  // delete vessels;
}

#if 0
void Simulation::testInsertion(Vessel* vessel) {
  std::vector<ActionLog> actioNLogs;
  // initialize each action
  vessel->insert(&actionLogs);
  for (size_t i = 0; i < TESTS_AMOUNT; ++i) {
    battleLog.recordAction(action)
  }
}

void Simulation::testSearch(Vessel* vessel) {
  for (size_t i = 0; i < TESTS_AMOUNT; ++i) {
    ActionLog actionLog = ActionLog("Search");
    vessel->calculate_damage(&actionLog);
    battleLog.recordAction(&action);
  }
}

void testElimination(Vessel* vessel) {
  for (size_t i = 0; i < TESTS_AMOUNT; ++i) {
    ActionLog actionLog = ActionLog("Elimination");
    vessel->upgrade(&actionLog);
    battleLog.recordAction(&action);
  }
}
#endif
