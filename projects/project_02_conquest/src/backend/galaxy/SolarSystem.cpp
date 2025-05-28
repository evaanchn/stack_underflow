// Copyright 2025 stack_underflow CC-BY 4.0

#include "SolarSystem.hpp"

SolarSystem::SolarSystem(std::vector<std::string>& solarSystemData) {
  this->planetGraph = new Graph<Planet*, size_t>(!DIRECTED);
  this->initSolarSystem(solarSystemData);
}

SolarSystem::~SolarSystem() {
  if (this->planetGraph) delete this->planetGraph;
  this->planetGraph = nullptr;
  for (auto *planet : this->planets) {
    if (planet) delete planet;
  }
  this->planets.clear();
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
  // Randomizer for coordinates creation
  Random<size_t> randNatural;

  // Current planet index is used as row (one planet per row)
  // Then, generate a random column from 0 to last column
  // in planetsAmount dimensioned matrix
  size_t row = planetIndex;
  size_t col = randNatural.generateRandomInRange(0, this->planetsCount - 1);
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
    this->entryPlanet->setMine();
    this->entryPlanet->removeBoss();
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
  // FOR EACH CONNECTION
  // CALCULATE DISCONNECTION PROBABILITY
  // IF DISCONNECT
  // IF CURRENT INDEX * INDEX >= AMOUNT OF ELEMENTS AND NOT AN ARTICULATION POINT
  // DISCONNECT
}

std::string SolarSystem::getName() const {
  return this->name;
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
