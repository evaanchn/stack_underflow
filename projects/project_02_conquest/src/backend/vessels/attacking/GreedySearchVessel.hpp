// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "GreedySearch.hpp"
#include "AttackVessel.hpp"

/// @brief Greedy search attack vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type

template<typename DataType, typename WeightType>
class GreedySearchVessel : public AttackVessel<DataType, WeightType> {
 public:
  /// Constructor
  GreedySearchVessel() {
    this->attackAlgorithm = new GreedySearch<DataType, WeightType>();
  }
};
