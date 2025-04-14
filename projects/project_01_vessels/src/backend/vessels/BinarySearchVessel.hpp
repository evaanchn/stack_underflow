// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <vector>

#include "BinarySearch.hpp"
#include "Vessel.hpp"

class BinarySearchVessel : public Vessel {
 public:
  BinarySearchVessel();
  // discard
  void fillVessel(std::vector<ActionLog>& logs) override {
  }
};
