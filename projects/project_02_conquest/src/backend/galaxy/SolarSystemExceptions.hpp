// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <stdexcept>
#include <string>

/* USAGE:
  try {
    // Invocation of method
  } catch (const SolarSystemException& e) {
    std::cerr << "Solar System error: " << e.what() << std::endl;
  }
*/

/// @brief Custom exception for Solar System creation
class SolarSystemException : public std::runtime_error {
 public:
  // Inherit constructors from std::runtime_error
  // to allow passing error messages
  using std::runtime_error::runtime_error;
};

class DataNotFoundException : public SolarSystemException {
 public:
  DataNotFoundException()
    : SolarSystemException("No data specified for solar system") {
  }
};

class InsufficientDataException : public SolarSystemException {
 public:
  InsufficientDataException()
    : SolarSystemException("Insufficient data to construct solar system") {
  }
};

class InsufficientPlanetsException : public SolarSystemException {
 public:
  InsufficientPlanetsException()
    : SolarSystemException("Solar System must contain at least two planets") {
  }
};

class MaxPlanetsExceededException : public SolarSystemException {
 public:
  MaxPlanetsExceededException()
    : SolarSystemException("Exceeded maximum amount of planets established") {
  }
};

class EntryExitCoincidenceException: public SolarSystemException {
 public:
  EntryExitCoincidenceException()
    : SolarSystemException("Entry planet and exit planet are the same") {
  }
};

class MissingEntryPlanetException: public SolarSystemException {
 public:
  MissingEntryPlanetException()
    : SolarSystemException("Entry planet not found in planets list") {
  }
};

class MissingExitPlanetException: public SolarSystemException {
 public:
  MissingExitPlanetException()
    : SolarSystemException("Exit planet not found in planets list") {
  }
};

class DuplicatePlanetException: public SolarSystemException {
 public:
  DuplicatePlanetException()
    : SolarSystemException("At least two planets share a name") {
  }
};
