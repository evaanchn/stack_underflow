// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#define ACTIVATION_COST 10

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "GreedySearch.hpp"
#include "AttackVessel.hpp"

/// @brief Greedy search assalt vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class GreedySearchVessel : public AssaltVessel<DataType, WeightType> {
 public:
  /// Constructor
  AssaltVessel() {
    this->AttackAlgorithm = new GreedySearch<DataType, WeightType>();
  }
};
