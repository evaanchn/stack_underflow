// Copyright 2025 stack_underflow CC-BY 4.0

// TODO (andrey): handle planets creation, ensuring that they are scaled
// accordingly and placed accordingly
// TODO (andrey): Every time a planet is created, setPlanetInteraction
// must be a lambda that places the index of the planet in selectedPlanet attr.
// Check UIBoard from project 1
// TODO (andrey): Add a UIPath class that connects two planets
// Paths should be stored in some sort of data structure in solar system
// And be handled. Path can be hidden. If necessary, must be able to show
// weight and path or just path

#pragma once

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_set>
#include <vector>

#include "Random.hpp"
#include "UIPlanet.hpp"
#include "../backend/galaxy/solar_system/planet/Planet.hpp"

#define NONE_SELECTED -1
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define RIGHT_HALF_START_X (WINDOW_WIDTH / 2)
#define MIN_MARGIN 20
#define MIN_PLANET_DISTANCE 30
#define NONE_SELECTED -1

class UISolarSystem {
 private:
  std::vector<UIPlanet*> UiPlanets;
  int selectedPlanet = NONE_SELECTED;

  const int areaWidth = WINDOW_WIDTH / 2 - MIN_MARGIN * 2;
  const int areaHeight = WINDOW_HEIGHT - MIN_MARGIN * 2;
  const int startX = RIGHT_HALF_START_X + MIN_MARGIN;

 public:
  UISolarSystem() = default;
  ~UISolarSystem();
  void createPlanets(std::vector<Planet*> planets);
  int getSelectedPlanet() const;

 private:
  std::vector<std::pair<int, int>> generateValidPositions(size_t count
      , const std::vector<int>& planetSizes);
  
  bool isValidPosition(int x, int y, int size
      , const std::vector<std::pair<int, int>>& positions
      , const std::vector<int>& sizes);
};
