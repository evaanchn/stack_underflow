// Copyright 2025 stack_underflow CC-BY 4.0

#include "ActionLog.hpp"

ActionLog::ActionLog(const std::string action)
: iterations(0)
, startTime()
, endTime() {
  setAction(action);
}

void ActionLog::setResponsible(const std::string responsible) {
  this->responsible = responsible;
}

void ActionLog::setAction(const std::string action) {
  this->action = action;
}

void ActionLog::recordStart() {
  this->startTime = clock();
}

void ActionLog::recordEnd(size_t iterations) {
  this->endTime = clock();
  this->iterations = iterations;
}

std::string ActionLog::getDuration() {
  double duration = static_cast<double> (this->endTime - this->startTime)
    / CLOCKS_PER_SEC * 1000;  // Conversion to ms
  return std::to_string(duration) + "ms";
}

size_t ActionLog::getIterations() {
  return this->iterations;
}

std::string ActionLog::toString() {
  std::string result = this->responsible + " - " + this->action
    + " | Iterations: " + std::to_string(this->iterations)
    + " Duration: " + getDuration();
  return result;
}
