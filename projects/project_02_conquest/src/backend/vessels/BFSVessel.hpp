// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#define ACTIVATION_COST 10

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "BFS.hpp"
#include "ProbingVessel.hpp"

/// @brief Breadth frst search probing
/// @tparam DataType planets type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class BFSVessel : public ProbingVessel<DataType, WeightType> {
 public:
  /// Constructor
  BFSVessel() {
    this->traversalAlgorithm = new BFS<DataType, WeightType>();
  }
};
