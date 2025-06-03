// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#define MAX_PLANETS 20

class SolarSystemVerifier {
 public:
 /**
  * @brief Analyzes the provided solar system data for structural and logical
  * correctness.
  * 
  * This method performs several validations on the input vector, including:
  * - Ensures the data is not empty.
  * - Verifies that it includes at least an entry and exit planet, plus one or
  * more planetary names.
  * - Ensures entry and exit planets are not the same.
  * - Checks for the existence of entry and exit planets within the planet list.
  * - Detects duplicate planet names.
  * 
  * @param solarSystemData A vector of strings containing the solar system data.
  *        The expected format is: [system_name, entry_planet, exit_planet
  *        , planet1, planet2, ...]
  * 
  * @throws DataNotFoundException If the data vector is empty.
  * @throws InsufficientDataException If the vector lacks even the entry planet.
  * @throws InsufficientPlanetsException If the vector lacks at least one planet
  *  in addition to the entry and exit.
  * @throws MaxPlanetsExceededException If the number of planets exceeds the
  * defined MAX_PLANETS limit.
  * @throws EntryExitCoincidenceException If the entry and exit planets are the
  * same.
  * @throws MissingEntryPlanetException If the entry planet does not exist in
  * the planet list.
  * @throws MissingExitPlanetException If the exit planet does not exist in the
  * planet list.
  * @throws DuplicatePlanetException If any planet name appears more than once
  * in the planet list.
  */
  void analyzeSolarSystemData(std::vector<std::string>& solarSystemData);

 /**
  * @brief Checks whether a specified planet exists in the list of planets.
  * 
  * This utility function iterates through the planetary portion of the solar
  * system
  * data and returns true if the specified planet name is found.
  * 
  * @param solarSystemData A vector of strings representing the full solar
  * system data.
  * @param planetName The name of the planet to search for in the
  * planet list.
  * @return true If the planet exists in the list.
  * @return false If the planet does not exist in the list.
  */
  bool planetExists(std::vector<std::string>& solarSystemData
      , std::string planetName);
};
