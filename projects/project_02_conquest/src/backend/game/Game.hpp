// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

#include "BattleLog.hpp"
#include "Coordinates.hpp"
#include "Galaxy.hpp"
#include "GameConstants.hpp"
#include "VesselsCollection.hpp"

struct Player {
  size_t etherium;  /// currency
  size_t activeMines;
};

class Game {
 private:
  /// Pointer to the Galaxy object containing solar systems
  Galaxy* galaxy;
  /// Pointer to the BattleLog object for logging actions
  BattleLog* battleLog;
  /// Player object containing purchase points and active mines
  Player player;
  /// Flag indicating if the game is over
  bool gameOver;

  VesselsCollection<Planet*, size_t> vessels;

 public:
  /// @brief constructor method of the class
  Game();
  /// @brief destructor method of the class
  ~Game();

  /// @brief Start the game objects with the given galaxy
  /// @param galaxyFileDirectory path to the galaxy CSV file
  /// @return true on success, false if the galaxy file could not be loaded
  bool startGame(const char* galaxyFileDirectory = GALAXY_FILE_PATH);

  /// @brief Uses a probing vessel to explore solar system planets
  /// @param vesselID ID of the vessel to be used in the probe
  /// @param startPlanetIndex planet where the probe starts
  /// @param probeLog
  /// @return true if the probe was successful, false otherwise
  bool probe(int vesselID, int startPlanetIndex, ActionLog& probeLog);

  /// @brief Uses a probing vessel to explore solar system planets
  /// @param vesselID ID of the vessel to be used in the probe
  /// @param startPlanetIndex planet where the probe starts
  /// @return true if the probe was successful, false otherwise
  bool probe(int vesselID, int startPlanetIndex);

  /// @brief Uses a scouting vessel to explore solar system paths
  /// @param vesselID ID of the vessel to be used in the scout
  /// @param startPlanetIndex planet where the scout starts
  /// @param scoutLog
  /// @return true if the scout was successful, false otherwise
  bool scout(int vesselID, int startPlanetIndex, ActionLog& scoutLog);

  /// @brief Uses a scouting vessel to explore solar system paths
  /// @param vesselID ID of the vessel to be used in the scout
  /// @param startPlanetIndex planet where the scout starts
  /// @return true if the scout was successful, false otherwise
  bool scout(int vesselID, int startPlanetIndex);

  /// @brief Sends an attack to a planet
  /// @param vesselID ID of the vessel to be used in the attack
  /// @param targetPlanetIndex planet to be attacked
  /// @param attackLog
  /// @return damage dealed || -1 not enough etherium || -2 planet has NO boss
  int attack(int vesselID, int targetPlanetIndex, DamageLog attackLog);

  /// @brief Sends an attack to a planet
  /// @param vesselID ID of the vessel to be used in the attack
  /// @param targetPlanetIndex planet to be attacked
  /// @return damage dealed || -1 not enough etherium || -2 planet has NO boss
  int attack(int vesselID, int targetPlanetIndex);

  /// Collects purchase points based on the number of active mines
  void collectEtherium();

  /// @brief Tries to consume purchase points if there is enough
  /// @param points number of purchase points to consume
  /// @return true on success, false if not enough points
  bool consumeEtherium(size_t points);

  /**
   * @brief checks if the current solar system is completed
   */
  bool isCurrentSolarSystemCompleted() const;

  /**
   * @brief sets a new turn for the game
   */
  bool passNextSolarSystem();

  /**
   * @brief checks if the game is over
   */
  bool isGameOver() const;

  /// @brief Getters
  Galaxy* getGalaxy() const;
  size_t getSystemsLeftCount() const;
  BattleLog* getBattleLog() const;
  VesselsCollection<Planet*, size_t>& getVessels();
  size_t getVesselsCount() const;
  size_t getCurrentRemainingBosses() const;
  size_t getCurrentMInes() const;
  size_t getCurrentEtherium() const;
};
