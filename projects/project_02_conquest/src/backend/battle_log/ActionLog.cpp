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
  srand48(time(NULL) + clock());
  clock_gettime(CLOCK_MONOTONIC, &startTime);
}

void ActionLog::recordEnd(size_t iterations) {
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  this->iterations = iterations;
}

std::string ActionLog::getDuration() {
  double duration = getDurationTime();
  return std::to_string(duration) + "ms";
}

size_t ActionLog::getIterations() {
  return this->iterations;
}

double ActionLog::getDurationTime() {
  return ((endTime.tv_sec - startTime.tv_sec) * 1e6  // s to ms
  + (endTime.tv_nsec - startTime.tv_nsec) * 1e-3);  // nanoseconds to ms
}

std::string ActionLog::getResponsible() {
  return this->responsible;
}

std::string ActionLog::getAction() {
  return this->action;
}

std::string ActionLog::toString() {
  std::string result = this->responsible + " - " + this->action
    + " | Iterations: " + std::to_string(this->iterations)
    + " Duration: " + getDuration();
  return result;
}

uint64_t ActionLog::iterationsMean(std::vector<ActionLog>& logs) {
  return ::iterationsMean<ActionLog>(logs);
}

long double ActionLog::durationMean(std::vector<ActionLog>& logs) {
  return ::durationMean<ActionLog>(logs);
}
