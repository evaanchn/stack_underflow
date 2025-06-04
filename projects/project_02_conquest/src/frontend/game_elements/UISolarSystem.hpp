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

#include <string>
#include <vector>

#include "UIPlanet.hpp"
#include "../backend/galaxy/solar_system/planet/Planet.hpp"

#define NONE_SELECTED -1

class UISolarSystem {
 private:
  std::vector<UIPlanet*> UiPlanets;
  int selectedPlanet = NONE_SELECTED;

 public:
  UISolarSystem() = default;
  void createPlanets(std::vector<Planet*> planets);
  int getSelectedPlanet() const;
};
