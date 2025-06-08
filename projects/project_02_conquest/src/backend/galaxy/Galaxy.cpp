// Copyright 2025 stack_underflow CC-BY 4.0

#include "Galaxy.hpp"

Galaxy::Galaxy(const char* galaxyFileDirectory)
  : currentSolarSystem(nullptr)
  , currentSolarSystemIndex(0)
  , solarSystemsLeft(0) {
  this->setUpGalaxy(galaxyFileDirectory);
}

Galaxy::~Galaxy() {
  this->destroyCurrentSolarSystem();
}

void Galaxy::setUpGalaxy(const char* galaxyFileDirectory) {
  // TODO(any) add try catch for galaxy instancing
  CSVReader reader = CSVReader();
  reader.decomposeLines(galaxyFileDirectory, this->solarSystemsData, true);
  this->solarSystemsLeft = this->solarSystemsData.size();
}

bool Galaxy::createCurrentSolarSystem() {
  std::vector<std::string>& currentSolarSystemData
      = this->solarSystemsData[this->currentSolarSystemIndex];
  try {
    SolarSystemVerifier().analyzeSolarSystemData(currentSolarSystemData);
    this->currentSolarSystem = new SolarSystem(currentSolarSystemData);
  } catch (const SolarSystemException& e) {
    std::cerr << "Solar System error with #" << this->currentSolarSystemIndex
      << ": " << e.what() << std::endl;
    return false;
  }
  ++this->currentSolarSystemIndex;
  return true;
}

void Galaxy::destroyCurrentSolarSystem() {
  if (this->currentSolarSystem) delete this->currentSolarSystem;
  --this->solarSystemsLeft;  // count as completed
  this->currentSolarSystem = nullptr;
}

bool Galaxy::passNextSolarSystem() {
  if (this->currentSolarSystemIndex < this->solarSystemsData.size()) {
    this->destroyCurrentSolarSystem();
    return this->createCurrentSolarSystem();
  }
  return false;
}

SolarSystem* Galaxy::getCurrentSolarSystem() {
  return this->currentSolarSystem;
}

size_t Galaxy::getSystemsLeftCount() const {
  return this->solarSystemsLeft;
}
