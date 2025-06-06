// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ArticulationPointsFinder.hpp"
#include "Graph.hpp"
#include "planet/Planet.hpp"
#include "Random.hpp"

enum SOL_SYS_DATA_POSITIONS {
  NAME_POS, ENTRY_PLANET_POS, EXIT_PLANET_POS, PLANETS_START_POS
};

#define MINE_BOSS_SPAWN_PROB 0.1
#define LINK_PROB 0.7
#define DISTANCE_MAGNIFIER 10
#define X_COORDS_MAGNIFIER 1

class SolarSystem {
 private:
  std::string name;
  size_t planetsCount;
  size_t bossesAlive;

  Graph<Planet*, size_t>* planetGraph;
  std::vector<Planet*> planets;
  std::unordered_map<Planet*, size_t> planetsIndexes;
  std::unordered_set<Planet*> exploredPlanets;
  std::vector<std::vector<bool>> revealedPaths;

  Planet* entryPlanet;
  Planet* exitPlanet;

 public:
  /// @brief Constructs a SolarSystem from parsed data.
  /// @param solarSystemData Vector containing system name
  /// , entry/exit planet names, and planet names.
  explicit SolarSystem(std::vector<std::string>& solarSystemData);

  /// @brief Destructor to clean up dynamically allocated memory.
  ~SolarSystem();

 private:
  /// @brief Initializes planets from input data.
  /// @param solarSystemData Vector containing planet and system information.
  void initSolarSystem(std::vector<std::string>& solarSystemData);

  /// @brief Sets coordinates for a given planet based on its index.
  /// @param currentPlanet Pointer to the planet.
  /// @param planetIndex Index of the planet in the list.
  void setPlanetCoordinates(Planet* currentPlanet, size_t planetIndex);

  /// @brief Identifies and stores entry and exit planets.
  /// @param currentPlanet Pointer to the planet being evaluated.
  /// @param solarSystemData Input data vector.
  void setEntryAndExit(Planet* currentPlanet
      , std::vector<std::string>& solarSystemData);

  /// @brief Sets up interconnections between all planets.
  void setPlanetsConnections();

  /// @brief Connects all planets to each other with weighted edges.
  void connectAllPlanets();

  /// @brief Adjusts the graph by probabilistically removing edges.
  void adjustPlanetsConnections();

 public:
  /// @brief Gets the name of the solar system.
  /// @return The system name.
  std::string getName() const;

  /// @brief Gets the number of planets in the solar system.
  /// @return The planet count.
  size_t getPlanetsCount() const;

  /// @brief Gets the entry planet of the solar system.
  /// @return Pointer to the entry planet.
  Planet* getEntryPlanet() const;

  /// @brief Gets a pointer to the planet graph.
  /// @return Pointer to the graph representing planet connections.
  Graph<Planet*, size_t>* getGraph();

  /// @brief Gets the set of planets that have been explored.
  /// @return Reference to the explored planets set.
  std::unordered_set<Planet*>& getExploredPlanets();

  /// @brief Gets the matrix of revealed paths between planets.
  /// @return Reference to the revealed paths matrix.
  std::vector<std::vector<bool>>& getRevealedPaths();

  /// @brief Gets the mapping of planets to their respective indexes.
  /// @return Reference to the map from Planet* to size_t index.
  std::unordered_map<Planet*, size_t>& getPlanetsIndexes();
  /// @brief Updates the status of a boss on a given planet and decrements the
  /// count of alive bosses if defeated.
  /// @param planet containing the boss to check.
  /// @return true if the boss is still alive, false if it was defeated.
  bool updateBossAlive(Planet* planet);
  /// @brief Counts the number of bosses that are still alive
  /// @return The count of alive bosses.
  size_t countBossesAlive();
  /// @brief Checks if the solar system is complete.
  /// @return True if all bosses are defeated, false otherwise.
  bool isComplete() const;
};
