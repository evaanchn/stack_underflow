// Copyright 2025 stack_underflow CC-BY 4.0

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SolarSystem.hpp"

SolarSystem::SolarSystem(std::vector<std::string>& solarSystemData) {
  this->planetGraph = new Graph<Planet*, size_t>(!DIRECTED);
  this->initSolarSystem(solarSystemData);
  this->setPlanetsConnections();
}

SolarSystem::~SolarSystem() {
  if (this->planetGraph) delete this->planetGraph;
  this->planetGraph = nullptr;
  // Clear planets
  for (auto *planet : this->planets) {
    if (planet) delete planet;
  }
  // Clear dirty pointers
  this->planets.clear();
  this->revealedPaths.clear();
  this->planetsIndexes.clear();
}

void SolarSystem::initSolarSystem(std::vector<std::string>& solarSystemData) {
  this->name = solarSystemData[NAME_POS];
  // Calculate amount of planets to create
  this->planetsCount = solarSystemData.size() - PLANETS_START_POS;
  // Randomizer for probability calculation
  Random<double> randDouble;

  // For loop to create planets
  for (size_t planetIndex = 0; planetIndex < this->planetsCount
      ; ++planetIndex) {
    std::string currentPlanetName
        = solarSystemData[planetIndex + PLANETS_START_POS];

    bool hasMine = randDouble.generateRandomInRange(0.0, 1.0)
        < MINE_BOSS_SPAWN_PROB;
    Planet* currentPlanet = new Planet(currentPlanetName, hasMine);

    // Add planet to graph
    this->planetGraph->addNode(new Node(currentPlanet));
    // Add planet to planets vector
    this->planets.push_back(currentPlanet);
    // Add index to planet-index map
    this->planetsIndexes[currentPlanet] = planetIndex;
    // Generate current planet's coordinates based on its index
    this->setPlanetCoordinates(currentPlanet, planetIndex);
    // Determine if current planet was entry or exit planet
    this->setEntryAndExit(currentPlanet, solarSystemData);
  }
}

void SolarSystem::setPlanetCoordinates(Planet* currentPlanet
    , size_t planetIndex) {
  // Current planet index is used as row (one planet per row)
  // Then, generate a random column from 0 to last column
  // in planetsAmount dimensioned matrix
  size_t row = planetIndex;
  size_t col = Random<size_t>().generateRandomInRange(/*FIRST COL*/ 0
      , this->planetsCount * X_COORDS_MAGNIFIER - 1);
  Coordinates* planetCoordinates = new Coordinates(row, col);
  currentPlanet->setCoordinates(planetCoordinates);
}

void SolarSystem::setEntryAndExit(Planet* currentPlanet
    , std::vector<std::string>& solarSystemData) {
  // Register the entry and exit planets names for later storage
  std::string entryPlanetName = solarSystemData[ENTRY_PLANET_POS];
  std::string exitPlanetName = solarSystemData[EXIT_PLANET_POS];
  // Store entry or exit planet pointer matches
  if (currentPlanet->getName() == entryPlanetName) {
    this->entryPlanet = currentPlanet;
    this->entryPlanet->setMine();  // Entry planet has mine
    this->entryPlanet->removeBoss();  // Entry planet cannot have a boss
  } else if (currentPlanet->getName() == exitPlanetName) {
    this->exitPlanet = currentPlanet;
  }
}

void SolarSystem::setPlanetsConnections() {
  this->connectAllPlanets();
  this->adjustPlanetsConnections();
}

void SolarSystem::connectAllPlanets() {
  // Obtain nodes vector to use add edge method
  std::vector<Node<Planet*>*> nodes = this->planetGraph->getNodes();
  // Adjusts starting planet from first position (0) to the pos before last
  for (size_t start = 0; start < this->planetsCount - 1; ++start) {
    // Obtain current starting planet
    Planet* currentStartingPlanet = this->planets[start];
    // Creates a "triangular" effect in traversal, since the connections are
    // two-way, thus symmetric.
    for (size_t index = start + 1; index < this->planetsCount; ++index) {
      Planet* currentPlanet = this->planets[index];
      // Calculate distance to the other planet (rounded)
      double distanceBetweenPlanets
          = currentStartingPlanet->getDistanceTo(currentPlanet);
      // Magnify distance to fit planet's logic
      size_t magnifiedDistance = static_cast<size_t>
          (std::round(distanceBetweenPlanets* DISTANCE_MAGNIFIER));
      // Add edge with magnified distance
      this->planetGraph->addEdge(nodes[start], nodes[index], magnifiedDistance);
    }
  }
}

void SolarSystem::adjustPlanetsConnections() {
  std::vector<std::vector<size_t>> adjacencyMatrix
      = this->planetGraph->getAdjacencyMatrix();
  std::vector<Node<Planet*>*> nodes = this->planetGraph->getNodes();
  // For every connection available (lower triangle of adjacency matrix,
  // since the graph used is undirected)
  for (size_t fromIdx = 1; fromIdx < adjacencyMatrix.size(); ++fromIdx) {
    for (size_t toIdx = 0; toIdx < fromIdx; ++toIdx) {
      if (adjacencyMatrix[fromIdx][toIdx] == defaultNoEdge<size_t>()) continue;
      std::unordered_set<Node<Planet*>*> unremovableNodes;
      ArticulationPointsFinder<Planet*, size_t>().findArticulationPoints
          (this->planetGraph, unremovableNodes);
      // If from node is an articulation point, skip its disconnections
      if (unremovableNodes.find(nodes[fromIdx]) != unremovableNodes.end())
          break;
      // Otherwise, calculate whether to disconnect or not for this to
      bool disconnect = Random<double>().generateRandomInRange(0.0, 1.0)
          < 1 - LINK_PROB;  // Complement of link is unlink prob
      if (disconnect) {
        // If the node to which we have a connection to is not an art. point
        if (unremovableNodes.find(nodes[toIdx]) == unremovableNodes.end()) {
          // Remove edge between them
          this->planetGraph->removeEdge(nodes[fromIdx], nodes[toIdx]);
        }
      }
    }
  }
}

std::string SolarSystem::getName() const {
  return this->name;
}

size_t SolarSystem::getPlanetsCount() const {
  return this->planetsCount;
}

Graph<Planet*, size_t>* SolarSystem::getGraph() {
  return this->planetGraph;
}

std::unordered_set<Planet*>& SolarSystem::getExploredPlanets() {
  return this->exploredPlanets;
}

std::vector<std::vector<bool>>& SolarSystem::getRevealedPaths() {
  return this->revealedPaths;
}

std::unordered_map<Planet*, size_t>& SolarSystem::getPlanetsIndexes() {
  return this->planetsIndexes;
}
