// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

<<<<<<<< HEAD:projects/project_02_conquest/src/backend/vessels/attacking/GreedySearchVessel.hpp
#include <ActionLog.hpp>
#include "GreedySearch.hpp"
#include "AttackVessel.hpp"

/// @brief Greedy search assalt vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type
========
#include "ActionLog.hpp"
#include "BFS.hpp"
#include "ProbingVessel.hpp"

/// @brief Breadth first search probing
/// @tparam DataType Graph's data type (Planet, for game)
/// @tparam WeightType node edges type (size_t, for game)
>>>>>>>> cb8d7490bd59c110d15f0e57d6f95c4c7e9b0bed:projects/project_02_conquest/src/backend/vessels/probing/BFSVessel.hpp
template<typename DataType, typename WeightType>
class GreedySearchVessel : public AssaltVessel<DataType, WeightType> {
 public:
  /// Constructor
  AssaltVessel() {
    this->AttackAlgorithm = new GreedySearch<DataType, WeightType>();
  }
};
