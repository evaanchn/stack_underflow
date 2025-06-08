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
  /// @brief Vector containing all solar systems data.
  std::vector<std::vector<std::string>> solarSystemsData;
  SolarSystem* currentSolarSystem;
  size_t currentSolarSystemIndex;
  size_t solarSystemsLeft;

 public:
  /// @brief Constructs a Galaxy from a CSV file containing solar systems data.
  explicit Galaxy(const char* galaxyFileDirectory);
  /// @brief  Destructor
  ~Galaxy();
  /// @brief Allocates a new SolarSystem based on the current index in the data.
  /// @return true if the SolarSystem was created successfully, false otherwise.
  bool createCurrentSolarSystem();
  /// @brief Destroys the current SolarSystem and resets the pointer.
  void destroyCurrentSolarSystem();
  /// @brief Advances to the next solar system in the data.
  /// @return true if there was a next solar system, false otherwise.
  bool passNextSolarSystem();

 private:
  void setUpGalaxy(const char* galaxyFileDirectory);

 public:
  SolarSystem* getCurrentSolarSystem();
  /// @brief Gets the number of solar systems left to explore.
  size_t getSystemsLeftCount() const;
};
