// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include <ActionLog.hpp>
#include "LocalSearch.hpp"
#include "AttackVessel.hpp"

/// @brief Local search attack vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class LocalSearchVessel : public AttackVessel<DataType, WeightType> {
 public:
  /// Constructor
  LocalSearchVessel() {
    this->attackAlgorithm = new LocalSearch<DataType, WeightType>();
  }
};
