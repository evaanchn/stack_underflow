// Copyright 2025 stack_underflow CC-BY 4.0

#include <vector>

#include "PlanetsPositioner.hpp"

void PlanetsPositioner::positionPlanets(std::vector<Planet*>& planets
    , size_t planetsCount) {
  if (planetsCount < 4) return;
  std::vector<bool> unoccupiedCols(planetsCount, true);
  std::vector<bool> unoccupiedAscendingCols(2*planetsCount + 1, true);
  std::vector<bool> unoccupiedDescendingCols(2*planetsCount + 1, true);
  this->positionPlanetsRecursive(planets, planetsCount, 0,
      unoccupiedCols, unoccupiedAscendingCols, unoccupiedDescendingCols);
}

bool PlanetsPositioner::positionPlanetsRecursive(std::vector<Planet*>& planets
    , size_t planetsCount, size_t row
    , std::vector<bool>& unoccupiedCols
    , std::vector<bool>& unoccupiedAscendingCols
    , std::vector<bool>& unoccupiedDescendingCols) {
  if (row == planetsCount) {
    return true;  // Found one full placement
  }

  // Randomize cols accesses so placements are different
  std::vector<size_t> colIndices(planetsCount);
  std::iota(colIndices.begin(), colIndices.end(), 0);
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::shuffle(colIndices.begin(), colIndices.end(), gen);

  for (size_t col : colIndices) {
    if (unoccupiedCols[col] &&
        unoccupiedAscendingCols[row + col] &&
        unoccupiedDescendingCols[row - col + planetsCount]) {
      // Mark flags for cols arrays
      unoccupiedCols[col] = false;
      unoccupiedAscendingCols[row + col] = false;
      unoccupiedDescendingCols[row - col + planetsCount] = false;
      // Re-position planet
      Coordinates* planetCoords = planets[row]->getCoordinates();
      planetCoords->row = row;
      planetCoords->col = col;

      if (positionPlanetsRecursive(planets, planetsCount, row + 1,
          unoccupiedCols, unoccupiedAscendingCols, unoccupiedDescendingCols)) {
        return true;  // Success: stop further recursion
      }
      // Backtrack
      unoccupiedCols[col] = true;
      unoccupiedAscendingCols[row + col] = true;
      unoccupiedDescendingCols[row - col + planetsCount] = true;
    }
  }
  return false;  // No valid position found for this row
}
