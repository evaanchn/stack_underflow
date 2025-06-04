// Copyright 2025 stack_underflow CC-BY 4.0

#include "UISolarSystem.hpp"

#include "Random.hpp"

void UISolarSystem::createPlanets(std::vector<Planet*> planets) {
  // TODO (ANDREY) add scaling logic, placement logic
  // TODO TEST IF THIS IS VALID (Make planet set the selected planet as the index
  // at moment of creation)
  // planet->setPlanetInteraction([this, index]() {this->selectedPlanet = index});
}

int UISolarSystem::getSelectedPlanet() const {
  return this->selectedPlanet;
}
