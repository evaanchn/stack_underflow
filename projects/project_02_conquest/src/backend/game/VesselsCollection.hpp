// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "BFSVessel.hpp"
#include "DFSVessel.hpp"
#include "DijkstraVessel.hpp"
#include "FloydVessel.hpp"
#include "GreedySearchVessel.hpp"
#include "LocalSearchVessel.hpp"
#include "ExhaustiveSearchVessel.hpp"
#include "ExhaustiveSearchPruneVessel.hpp"

/// @brief Collection of all space vessels used in the game
/// @tparam DataType Type of data the vessel will handle (e.g., Planet*).
template<typename DataType, typename WeightType>
struct VesselsCollection {
  /// @brief Collection of probing vessels used in the game
  BFSVessel<DataType, WeightType> bfs;
  DFSVessel<DataType, WeightType> dfs;
  std::vector<ProbingVessel<DataType, WeightType>*> probingVessels = {
    &bfs, &dfs
  };
  /// @brief Collection of scouting vessels used in the game
  DijkstraVessel<DataType, WeightType> dijkstra;
  FloydVessel<DataType, WeightType> floyd;
  std::vector<ScoutingVessel<DataType, WeightType>*> scoutingVessels = {
    &dijkstra, &floyd
  };
  /// @brief Collection of attack vessels used in the game
  GreedySearchVessel<DataType, WeightType> greedySearch;
  LocalSearchVessel<DataType, WeightType> localSearch;
  ExhaustiveSearchVessel<DataType, WeightType> exhaustiveSearch;
  ExhaustiveSearchPruneVessel<DataType, WeightType> exhaustiveSearchPrune;
  std::vector<AttackVessel<DataType, WeightType>*> attackVessels = {
    &greedySearch, &localSearch, &exhaustiveSearch, &exhaustiveSearchPrune
  };
  size_t vesselsCount = TOTAL_VESSELS;
};
