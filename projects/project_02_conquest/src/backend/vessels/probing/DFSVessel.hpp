// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "ActionLog.hpp"
#include "DFS.hpp"
#include "ProbingVessel.hpp"

/// @brief Depth frst search probing
/// @tparam DataType Graph's data type (Planet, for game)
/// @tparam WeightType node edges type (size_t, for game)
template<typename DataType, typename WeightType>
class DFSVessel : public ProbingVessel<DataType, WeightType> {
 public:
  /// Constructor
  DFSVessel() {
    this->traversalAlgorithm = new DFS<DataType, WeightType>();
  }
};
