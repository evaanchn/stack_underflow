// Copyright 2025 stack_underflow CC-BY 4.0

#include "BinarySearchVessel.hpp"

BinarySearchVessel::BinarySearchVessel()
: Vessel("Wales", /* Health */ 100, /* Cost */ 80, /* Weight */ 2) {
  this->algorithm = new BinarySearch();
}

void BinarySearchVessel::fillVessel(std::vector<ActionLog>& logs) {
  logs.resize(ELEMENT_COUNT);
  int64_t element = 1;
  for (ActionLog& log : logs) {
    this->insert(element, log);
    ++element;
  }
}
