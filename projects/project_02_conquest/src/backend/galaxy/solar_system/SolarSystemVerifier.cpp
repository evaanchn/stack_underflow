// Copyright 2025 stack_underflow CC-BY 4.0

#include <unordered_set>
#include <string>

#include "SolarSystemVerifier.hpp"

#include "SolarSystem.hpp"
#include "SolarSystemExceptions.hpp"

void SolarSystemVerifier::analyzeSolarSystemData(std::vector<std::string>&
    solarSystemData) {
  // Empty data sent
  if (solarSystemData.empty()) throw DataNotFoundException();
  // If data doesn't specify more than name, entry planet, and exit planet
  else if (solarSystemData.size() < PLANETS_START_POS + 1)
      throw InsufficientDataException();
  // If only one planet was specified
  else if (solarSystemData.size() < PLANETS_START_POS + 2)
      throw InsufficientPlanetsException();
  // If there are more planets than the established amount + obligatory data
  else if (solarSystemData.size() > MAX_PLANETS + 3)
      throw MaxPlanetsExceededException();

  // If entry planet and exit planet are the same
  if (solarSystemData[ENTRY_PLANET_POS] == solarSystemData[EXIT_PLANET_POS]) {
    throw EntryExitCoincidenceException();
  }

  // If entry planet is not in the planet's list
  if (!planetExists(solarSystemData, solarSystemData[ENTRY_PLANET_POS]))
      throw MissingEntryPlanetException();
  // or if exit planet is not in the list
  else if (!planetExists(solarSystemData, solarSystemData[EXIT_PLANET_POS]))
      throw MissingExitPlanetException();

  // Verify if there are duplicates in solar system
  std::unordered_set<std::string> knownPlanetNames;
  for (size_t i = PLANETS_START_POS; i < solarSystemData.size(); ++i) {
    if (knownPlanetNames.find(solarSystemData[i]) != knownPlanetNames.end()) {
      throw DuplicatePlanetException();
    }
    knownPlanetNames.insert(solarSystemData[i]);
  }
}

bool SolarSystemVerifier::planetExists(std::vector<std::string>&
    solarSystemData, std::string planetName) {
  for (size_t i = PLANETS_START_POS; i < solarSystemData.size(); ++i) {
    if (solarSystemData[i] == planetName) return true;
  }
  return false;
}
