// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <iostream>
#include <vector>

#include "Algorithm.hpp"
#include "BFS.hpp"

/// Parent class for space vessels
class SpaceVessel {
 protected:
  /// usage cost
  size_t activationCost;
 public:
  /// Constructor
  explicit SpaceVessel(size_t costInit);

  /// @brief Get vessel cost
  /// @return activation cost according to the currency
  size_t getActivationCost();
};
