// Copyright 2025 stack_underflow CC-BY 4.0

#include "Algorithm.hpp"

algorithm::algorithm() {
  elementCount = 0;
}

std::string algorithm::getAlgorithmName() {
  return algorithmName;
}

size_t algorithm::getElementCount() {
  return elementCount;
}

void algorithm::increaseElementCount() {
  ++elementCount;
}

void algorithm::setAlgorithmName(std::string _algorithmName) {
  algorithmName = _algorithmName;
}
