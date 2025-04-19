// Copyright 2025 stack_underflow CC-BY 4.0

#include "Algorithm.hpp"

Algorithm::Algorithm() = default;
Algorithm::~Algorithm() = default;

std::string Algorithm::getName() {
  return this->algorithmName;
}

size_t Algorithm::getElementCount() {
  return this->elementRecord.size();
}
