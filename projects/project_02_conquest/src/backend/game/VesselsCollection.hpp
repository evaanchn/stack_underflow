// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <Planet.hpp>

#include "BFSVessel.hpp"
#include "DFSVessel.hpp"
#include "DijkstraVessel.hpp"
#include "FloydVessel.hpp"
#include "GreedySearchVessel.hpp"
#include "LocalSearchVessel.hpp"
#include "ExhaustiveSearchVessel.hpp"
#include "ExhaustiveSearchPruneVessel.hpp"

#define TOTAL_VESSELS 8

#define PROBE_LIMIT 3

enum SPACE_VESSEL_TYPE {
  BFS_VESSEL = 0,
  DFS_VESSEL,
  DIJKSTRA_VESSEL,
  FLOYD_VESSEL,
  GREEDY_VESSEL,
  LOCAL_SEARCH_VESSEL,
  EXHAUSTIVE_SEARCH_VESSEL,
  EXHAUSTIVE_PRUNE_VESSEL
};

/// @brief Collection of all space vessels used in the game
/// @tparam DataType Type of data the vessel will handle (e.g., Planet*).
template<typename DataType, typename WeightType>
struct VesselsCollection {
  DijkstraVessel<DataType, WeightType> dijkstra;
  BFSVessel<DataType, WeightType> bfs;
  DFSVessel<DataType, WeightType> dfs;
  FloydVessel<DataType, WeightType> floyd;
  GreedySearchVessel<DataType, WeightType> greedySearch;
  LocalSearchVessel<DataType, WeightType> localSearch;
  ExhaustiveSearchVessel<DataType, WeightType> exhaustiveSearch;
  ExhaustiveSearchPruneVessel<DataType, WeightType> exhaustiveSearchPrune;
  size_t vesselsCount = TOTAL_VESSELS;
};
