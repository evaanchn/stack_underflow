// Copyright 2025 stack_underflow CC-BY 4.0

#include "UISolarSystem.hpp"

#include "Random.hpp"

UISolarSystem::~UISolarSystem() {
  for (auto planet : UiPlanets) {
    delete planet;
  }
  UiPlanets.clear();
}

void UISolarSystem::createPlanets(std::vector<Planet*> planets) {
  for (auto planet : UiPlanets) {
    delete planet;
  }
  UiPlanets.clear();
  
  std::vector<int> planetSizes;
  Random<int> random;
  for (size_t i = 0; i < planets.size(); ++i) {
    planetSizes.push_back(random.generateRandomInRange(40, 100));
  }

  auto positions = generateValidPositions(planets.size(), planetSizes);

  for (size_t i = 0; i < planets.size(); ++i) {
    int x = positions[i].first;
    int y = positions[i].second;
    int size = planetSizes[i];
    
    UIPlanet* uiPlanet = new UIPlanet(x, y, size);
    uiPlanet->setPlanetInteraction([this, i]() { 
      this->selectedPlanet = static_cast<int>(i); 
    });
    uiPlanet->reveal();
    
    UiPlanets.push_back(uiPlanet);
  }
}

std::vector<std::pair<int, int>> UISolarSystem::generateValidPositions(
    size_t count, const std::vector<int>& planetSizes) {
  std::vector<std::pair<int, int>> positions;
  std::unordered_set<int> usedYValues;
  Random<int> random;
  
  int maxAttempts = 1000;
  
  for (size_t i = 0; i < count; ++i) {
    int size = planetSizes[i];
    bool positionFound = false;
    int attempts = 0;
    
    while (!positionFound && attempts < maxAttempts) {
      attempts++;
      
      int x = random.generateRandomInRange(startX, startX + areaWidth - size);
      int y = random.generateRandomInRange(MIN_MARGIN, 
                                         MIN_MARGIN + areaHeight - size);
      
      if (usedYValues.find(y) != usedYValues.end()) {
        continue;
      }
      
      if (isValidPosition(x, y, size, positions, planetSizes)) {
        positions.emplace_back(x, y);
        usedYValues.insert(y);
        positionFound = true;
      }
    }
    
    if (!positionFound) {
      int y = MIN_MARGIN;
      while (usedYValues.find(y) != usedYValues.end()) {
        y += MIN_PLANET_DISTANCE + planetSizes[i];
        if (y > MIN_MARGIN + areaHeight - size) {
          y = MIN_MARGIN;
        }
      }
      
      int x = startX + (i % 2) * (areaWidth / 2);
      positions.emplace_back(x, y);
      usedYValues.insert(y);
    }
  }
  
  return positions;
}

bool UISolarSystem::isValidPosition(int x, int y, int size, 
                                   const std::vector<std::pair<int, int>>& positions,
                                   const std::vector<int>& sizes) {
  for (size_t i = 0; i < positions.size(); ++i) {
    int otherX = positions[i].first;
    int otherY = positions[i].second;
    int otherSize = sizes[i];
    
    int centerX = x + size / 2;
    int centerY = y + size / 2;
    int otherCenterX = otherX + otherSize / 2;
    int otherCenterY = otherY + otherSize / 2;
    
    double distance = std::sqrt(std::pow(centerX - otherCenterX, 2) + 
                              std::pow(centerY - otherCenterY, 2));
    
    if (distance < (size + otherSize) / 2 + MIN_PLANET_DISTANCE) {
      return false;
    }
  }
  return true;
}

int UISolarSystem::getSelectedPlanet() const {
  return selectedPlanet;
}
