// Copyright 2025 stack_underflow CC-BY 4.0

#include "Vessel.hpp"


Vessel::Vessel(std::string nameInit, int64_t healthInit, size_t costInit
  , size_t weightInit)
: algorithm(nullptr)
, name(nameInit)
, health(healthInit)
, cost(costInit)
, weight(weightInit) {
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
  size_t iterations = 0;
  iterations = algorithm->remove(element);
  log.recordEnd(iterations);
  return iterations;
}

void Vessel::fillVessel(std::vector<ActionLog>& logs) {
  std::vector<int> numbers;
  for (int i = 1; i <= ELEMENT_COUNT; ++i) {
    numbers.push_back(i);
  }
  shuffle(numbers);
  logs.resize(ELEMENT_COUNT);
  for (ActionLog& log : logs) {
    if (numbers.empty()) break;
    this->insert(numbers.back(), log);
    numbers.pop_back();
  }
}

bool Vessel::isAlive() {
  return (this->health > 0);
}

size_t Vessel::getWeight() {
  return this->weight;
}

size_t Vessel::getCost() {
  return this->cost;
}

void Vessel::takeDamage(int64_t damage_dealed) {
  if (this->isAlive()) {
    this->health -= damage_dealed;
  }
}

int Vessel::calculateDamage(ActionLog& log) {
  int damage = 0;
  int64_t randNum = this->randValue(1, ELEMENT_COUNT);
  int deduction = this->search(randNum, log);
  // calculate damage
  if (deduction != 0) damage = MAX_DAMAGE / deduction;
  return damage;
}

bool Vessel::upgradeVessel(const size_t upgradePoints
    , std::vector<ActionLog>& logs) {
  ActionLog logDelete = ActionLog("delete");
  int64_t element = this->randValue(1, ELEMENT_COUNT);
  size_t iterations = this->deletion(element, logDelete);
  logs.push_back(logDelete);
  if (iterations > upgradePoints) {
    ActionLog reInsertion = ActionLog("search");
    // put element back
    this->insert(element, reInsertion);
    logs.push_back(reInsertion);
    return false;
  }
  return true;
}

void Vessel::shuffle(std::vector<int>& numbers) {
  std::default_random_engine rng(time(0));
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::shuffle(numbers.begin(), numbers.end(), rng);
}

int64_t Vessel::randValue(int64_t min, int64_t max) {
  static thread_local std::mt19937_64 rng(std::random_device{}());
  std::uniform_int_distribution<int64_t> dist(min, max);
  return dist(rng);
}
