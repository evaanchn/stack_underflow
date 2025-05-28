// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Graph.hpp"
#include "Planet.hpp"
#include "Random.hpp"

enum SOL_SYS_DATA_POSITIONS {
  NAME_POS, ENTRY_PLANET_POS, EXIT_PLANET_POS, PLANETS_START_POS
};

#define MINE_BOSS_SPAWN_PROB 0.1
#define LINK_PROB 0.05
#define DISTANCE_MAGNIFIER 10

class SolarSystem {
 private:
  std::string name;
  size_t planetsCount;

  Graph<Planet*, size_t>* planetGraph = nullptr;
  std::unordered_set<Planet*> exploredPlanets = std::unordered_set<Planet*>();
  std::vector<std::vector<bool>> revealedPaths
      = std::vector<std::vector<bool>>();
  std::vector<Planet*> planets = std::vector<Planet*>();
  std::unordered_map<Planet*, size_t> planetsIndexes
      = std::unordered_map<Planet*, size_t>();

  Planet* entryPlanet = nullptr;
  Planet* exitPlanet = nullptr;

 public:
  SolarSystem() = default;
  SolarSystem(std::vector<std::string>& solarSystemData);
  ~SolarSystem();
  void setPlanetsConnections();
 private:
  void initSolarSystem(std::vector<std::string>& solarSystemData);
  void setPlanetCoordinates(Planet* currentPlanet, size_t planetIndex);
  void setEntryAndExit(Planet* currentPlanet
      , std::vector<std::string>& solarSystemData);

 private:
  
  void connectAllPlanets();
  void adjustPlanetsConnections();

 public:
  std::string getName() const;
  Graph<Planet*, size_t>* getGraph();
  std::unordered_set<Planet*>& getExploredPlanets();
  std::vector<std::vector<bool>>& getRevealedPaths();
  std::unordered_map<Planet*, size_t>& getPlanetsIndexes();
  Planet* getEntryPlanet();
  Planet* getExitPlanet();
};
