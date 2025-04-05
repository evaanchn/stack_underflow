// Copyright 2025 stack_underflow CC-BY 4.0

#include "Vessel.hpp"

Vessel::Vessel(std::string nameInit, int64_t healthInit, size_t costInit
    , size_t weightInit)
: name(nameInit)
, health(healthInit)
, cost(costInit)
, weight(weightInit) {
}

int Vessel::search(int value/*, ActionLog& log*/) {
  /*
  log.setResponsible(algorithm.getName());
  log.setAction("search");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm.search(value);
  log.recordEnd(iterations);
  return iterations;
  */
}

int Vessel::insert(int value/*, ActionLog& log*/) {
  /*
  log.setResponsible(algorithm.getName());
  log.setAction("insert");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm.insert(value);
  log.recordEnd(iterations);
  return iterations;
  */
}

int Vessel::deletion(int value, size_t& upgrade_points/*, ActionLog& log*/) {
  /*
  log.setResponsible(algorithm.getName());
  log.setAction("delete");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm.deletion(value, upgrade_points);
  log.recordEnd(iterations);
  return iterations;
  */
}

void Vessel::fillVessel(/*std::vector<ActionLog>& logs*/) {
  std::vector<int> numbers;
  for (int i = 0; i <= ELEMENT_COUNT; ++i) {
    numbers.push_back(i);
  }
  //TODO(any): shuffle numbers
  /*
  for (ActionLog log : logs) {
    if (numbers.empty()) break;
    this->insert(numbers.back(), log)
    numbers.pop_back();
  }
  */
}

bool Vessel::isAlive() {
  return (this->health > 0);
}

void Vessel::takeDamage(int64_t damage_dealed) {
  if (this->isAlive()) {
    this->health -= damage_dealed;
  }
}

int Vessel::calculateDamage(/*ActionLog& log*/) {
  int damage = 0;
  // create random
  std::srand(std::time(nullptr));
  int random_number = (std::rand() % 50) + 1;
  // search random
  int deduction = this->search(random_number/*, ActionLog& log*/);
  // calculate damage
  damage = MAX_DAMAGE / deduction;
  return damage;
}
