// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#define GALAXY_FILE_PATH "tests/andromeda_systems.csv"

// ACTIONS
enum ACTIONS {
  NO_ACTION = -1, PROBE, SCOUT, ATTACK
};

// limitations
#define PROBE_LIMIT 3

// damage
#define MAX_DAMAGE 50

// currency
#define MAX_ETHERIUM 999
#define ETHERIUM_INC 10  // etherium points increment
#define ETHERUM_PRODUCTION_TIME 5  // seconds

// Space vessels
#define TOTAL_VESSELS 8
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
#define BFS_COST  10
#define DFS_COST  10
#define DIJKSTRA_COST  20
#define FLOYD_COST  30
#define GREEDY_COST  35
#define LOCALSEARCH_COST  40
#define EXHAUSTIVE_COST  45
#define EXHAUSTIVEPRUNE_COST  50

const std::vector<size_t> VESSELS_COSTS = {
    BFS_COST, DFS_COST, DIJKSTRA_COST, FLOYD_COST
    , GREEDY_COST, LOCALSEARCH_COST, EXHAUSTIVE_COST, EXHAUSTIVEPRUNE_COST
};

#define INSUFICIENT_ETHERIUM -1
#define HAS_NO_BOSS -2
