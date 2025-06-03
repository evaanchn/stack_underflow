// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "ExhaustiveSearchPrune.hpp"
#include "AttackVessel.hpp"

/// @brief Exhaustive search prune attack vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type

template<typename DataType, typename WeightType>
class ExhaustiveSearchPruneVessel : public AttackVessel<DataType, WeightType> {
 public:
  /// Constructor
  ExhaustiveSearchPruneVessel() {
    this->AttackAlgorithm = new ExhaustiveSearchPruneVessel<DataType
        , WeightType>();
  }
};
