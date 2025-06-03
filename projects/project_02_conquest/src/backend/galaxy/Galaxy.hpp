// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "CSVReader.hpp"
#include "SolarSystem.hpp"
#include "SolarSystemExceptions.hpp"
#include "SolarSystemVerifier.hpp"

class Galaxy {
 private:
  std::vector<std::vector<std::string>> solarSystemsData;
  SolarSystem* currentSolarSystem;
  size_t currentSolarSystemIndex = 0;

 public:
  explicit Galaxy(const char* galaxyFileDirectory);
  ~Galaxy();
  void createCurrentSolarSystem();
  void destroyCurrentSolarSystem();

 private:
  void setUpGalaxy(const char* galaxyFileDirectory);
 
 public:
  SolarSystem* getCurrentSolarSystem();
};
