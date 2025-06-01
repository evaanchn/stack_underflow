// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "ActionLog.hpp"
#include "Dijkstra.hpp"
#include "ScoutingVessel.hpp"

/// @brief Dijkstra scouting vessel
/// @tparam DataType Graph's data type (Planet, for game)
/// @tparam WeightType node edges type (size_t, for game)
template<typename DataType, typename WeightType>
class DijkstraVessel : public ScoutingVessel<DataType, WeightType> {
 public:
  /// Constructor
  DijkstraVessel() {
    this->pathingAlgorithm = new Dijkstra<DataType, WeightType>();
  }
};
