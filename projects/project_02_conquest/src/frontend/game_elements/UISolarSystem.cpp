// Copyright 2025 stack_underflow CC-BY 4.0

#include "UISolarSystem.hpp"

UISolarSystem::UISolarSystem()
: planetSelectedSound(SOUND_PLANET_SELECTED, false) {
  this->mineSprite = new Fl_PNG_Image(MINE_SPRITE_PATH.c_str());
}

UISolarSystem::~UISolarSystem() {
  for (size_t fromIdx = 1; fromIdx < this->UiPaths.size(); ++fromIdx) {
    for (size_t toIdx = 0; toIdx < fromIdx; ++toIdx) {
      if (this->UiPaths[fromIdx][toIdx]) delete this->UiPaths[fromIdx][toIdx];
    }
  }
  UiPaths.clear();

  for (auto planet : this->UiPlanets) {
    delete planet;
  }
  UiPlanets.clear();

  if (this->mineSprite) delete this->mineSprite;
  this->mineSprite = nullptr;
}

void UISolarSystem::createPlanets(std::vector<Planet*> planets) {
  for (auto planet : UiPlanets) {
    delete planet;
  }
  UiPlanets.clear();

  for (size_t i = 0; i < planets.size(); ++i) {
    int size = RIGHT_HALF_START_X / planets.size();
    int x = size * planets[i]->getCoordinates()->col + RIGHT_HALF_START_X
        - MIN_MARGIN;
    int y = size * planets[i]->getCoordinates()->row + MIN_MARGIN * 2;

    if (x > WINDOW_WIDTH) x -= (size + MIN_MARGIN);
    if (y > WINDOW_HEIGHT) y -= (size + MIN_MARGIN);
    
    UIPlanet* uiPlanet = new UIPlanet(x, y, size);
    if (planets[i]->hasBoss()) {
      Fl_PNG_Image boss = Fl_PNG_Image(BOSS_SPRITE_PATH.c_str());
      uiPlanet->setOccupier(&boss);
    } else {
      // If does not have boss but has mine, it is entry planet
      if (planets[i]->hasMine()) {
        uiPlanet->setOccupier(this->mineSprite);
        uiPlanet->reveal();
      }
    }

    // Planet stores in selected planet, its index
    uiPlanet->setPlanetInteraction([this, i]() { 
      this->selectedPlanet = static_cast<int>(i);
      this->planetSelectedSound.play();
    });
    UiPlanets.push_back(uiPlanet);
  }
}

void UISolarSystem::createPaths(Graph<Planet*, size_t>* graph
    , Fl_Group* solarSystemArea) {
  auto& adjacencyMatrix = graph->getAdjacencyMatrix();
  this->UiPaths.resize(adjacencyMatrix.size());
  for (size_t fromIdx = 1; fromIdx < adjacencyMatrix.size(); ++fromIdx) {
    this->UiPaths[fromIdx].resize(adjacencyMatrix[fromIdx].size());
    for (size_t toIdx = 0; toIdx < fromIdx; ++toIdx) {
      size_t weight = adjacencyMatrix[fromIdx][toIdx];
      if (weight != defaultNoEdge<size_t>()) {
        UIPlanet* uiSource = this->UiPlanets[fromIdx];
        UIPlanet* uiDestiny = this->UiPlanets[toIdx];
        if (uiSource && uiDestiny) {
          UIPath* path = new UIPath(uiSource, uiDestiny, weight
              , DEFAULT_PATH_COLOR);
          solarSystemArea->add(path);
          this->UiPaths[fromIdx][toIdx] = path;
        }
      }
    }
  }
  // Re-add planets so they are on top
  for (auto* planet : this->UiPlanets) {
    solarSystemArea->remove(planet->getButton());
    solarSystemArea->add(planet->getButton());
  }
}

int UISolarSystem::obtainSelectedPlanet() {
  int selected = this->selectedPlanet;
  // reset taken selection
  this->selectedPlanet = NONE_SELECTED;
  return selected;
}

void UISolarSystem::updatePathsVisibility(
    std::vector<std::vector<bool>>& pathsRevealed) {
  for (size_t fromIdx = 1; fromIdx < pathsRevealed.size(); ++fromIdx) {
    for (size_t toIdx = 0; toIdx < fromIdx; ++toIdx) {
      if (pathsRevealed[fromIdx][toIdx]) {
        if (this->UiPaths[fromIdx][toIdx])
            this->UiPaths[fromIdx][toIdx]->reveal();
      }
    } 
  }
}

void UISolarSystem::updatePlanetsVisibility(
    std::unordered_set<Planet*> exploredPlanets, std::vector<Planet*> planets) {
  for (size_t i = 0; i < planets.size(); ++i) {
    if (exploredPlanets.find(planets[i]) != exploredPlanets.end()) {
      this->UiPlanets[i]->reveal();
    }
  }
}

void UISolarSystem::revealPlanet(size_t planetIdx) {
  this->UiPlanets[planetIdx]->reveal();
}


void UISolarSystem::removeBoss(int planetIdx) {
  this->UiPlanets[planetIdx]->removeOccupier();
  this->UiPlanets[planetIdx]->setOccupier(this->mineSprite);
}
