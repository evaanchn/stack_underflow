// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "ExhaustiveSearch.hpp"
#include "AttackVessel.hpp"

/// @brief Exhaustive search attack vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type

template<typename DataType, typename WeightType>
class ExhaustiveSearchVessel : public AttackVessel<DataType, WeightType> {
 public:
  /// Constructor
  ExhaustiveSearchVessel() {
    this->attackAlgorithm = new ExhaustiveSearch<DataType, WeightType>();
  }
};
