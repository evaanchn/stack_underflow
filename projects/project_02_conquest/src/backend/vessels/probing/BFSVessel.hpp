// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "ActionLog.hpp"
#include "BFS.hpp"
#include "ProbingVessel.hpp"

/// @brief Breadth first search probing
/// @tparam DataType Graph's data type (Planet, for game)
/// @tparam WeightType node edges type (size_t, for game)
template<typename DataType, typename WeightType>
class BFSVessel : public ProbingVessel<DataType, WeightType> {
 public:
  /// Constructor
  BFSVessel() {
    this->traversalAlgorithm = new BFS<DataType, WeightType>();
  }
};
