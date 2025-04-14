// Copyright 2025 stack_underflow CC-BY 4.0

#include "Vessel.hpp"


Vessel::Vessel(std::string nameInit, int64_t healthInit, size_t costInit
  , size_t weightInit)
: name(nameInit)
, health(healthInit)
, cost(costInit)
, weight(weightInit)
, algorithm(nullptr) {
}

Vessel::~Vessel() {
  delete this->algorithm;
  this->algorithm = nullptr;
}

size_t Vessel::search(int64_t element, ActionLog& log) {
  log.setResponsible(algorithm->getName());
  log.setAction("search");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm->search(element);
  log.recordEnd(iterations);
  return iterations;
}

size_t Vessel::insert(int64_t element, ActionLog& log) {
  log.setResponsible(algorithm->getName());
  log.setAction("insert");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm->insert(element);
  log.recordEnd(iterations);
  return iterations;
}

size_t Vessel::deletion(int64_t element, ActionLog& log) {
  log.setResponsible(algorithm->getName());
  log.setAction("delete");
  log.recordStart();
  // receives the iterations from algorithm method
  size_t iterations = algorithm->remove(element);
  log.recordEnd(iterations);
  return iterations;
  return 2;
}

void Vessel::fillVessel(std::vector<ActionLog>& logs) {
  std::vector<int> numbers;
  for (int i = 0; i <= ELEMENT_COUNT; ++i) {
    numbers.push_back(i);
  }
  shuffle(numbers);
  for (ActionLog log : logs) {
    if (numbers.empty()) break;
    this->insert(numbers.back(), log);
    numbers.pop_back();
  }
}

const bool Vessel::isAlive() {
  return (this->health > 0);
}

const size_t Vessel::getWeight() {
  return this->weight;
}

const size_t Vessel::getCost() {
  return this->cost;
}

void Vessel::takeDamage(int64_t damage_dealed) {
  if (this->isAlive()) {
    this->health -= damage_dealed;
  }
}

int Vessel::calculateDamage(ActionLog& log) {
  int damage = 0;
  int deduction = this->search(randValue(1, ELEMENT_COUNT), log);
  // calculate damage
  damage = MAX_DAMAGE / deduction;
  return damage;
}

bool Vessel::upgradeVessel(size_t& upgradePoints, ActionLog& log) {
  int64_t element = this->randValue(1, ELEMENT_COUNT);
  size_t iterations = this->deletion(element, log);
  if (iterations > upgradePoints) {
    upgradePoints = 0;
    ActionLog temp = ActionLog("search");
    // put element back
    this->insert(element, temp);
    return false;
  }
  upgradePoints -= iterations;
  return true;
}

void Vessel::shuffle(std::vector<int> numbers) {
  std::default_random_engine rng(time(0));
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::shuffle(numbers.begin(), numbers.end(), rng);
}

int64_t randValue(int64_t min, int64_t max) {
  std::srand(std::time(nullptr));
  return (int64_t)(std::rand() % 50) + 1;
}
