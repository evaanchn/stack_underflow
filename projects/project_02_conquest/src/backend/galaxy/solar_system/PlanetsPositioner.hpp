// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <vector>
#include <random>
#include <algorithm>

#include "planet/Planet.hpp"

#define UNOCCUPIED true

class PlanetsPositioner {
 public:
  PlanetsPositioner() = default;
  /// @brief Positions planets so that none are immediately next to each other
  /// @param planets Vector of planets to position
  /// @param planetsCount Amount of planets in vector
  void positionPlanets(std::vector<Planet*>& planets, size_t planetsCount);

 private:
  /// @brief Recursive method that positions one planet per row
  /// @param planets Vector of planets to position
  /// @param planetsCount Amount of planets
  /// @param row Current row placing
  /// @param unoccupiedCols Cols available
  /// @param unoccupiedAscendingCols Ascending cols available
  /// @param unoccupiedDescendingCols Descending cols available
  /// @return true if could find full placement
  bool positionPlanetsRecursive(std::vector<Planet*>& planets
      , size_t planetsCount, size_t row
      , std::vector<bool>& unoccupiedCols
      , std::vector<bool>& unoccupiedAscendingCols
      , std::vector<bool>& unoccupiedDescendingCols);
};
