// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

#include "BattleLog.hpp"
#include "Coordinates.hpp"
#include "Galaxy.hpp"
#include "VesselsCollection.hpp"

// TODO(any): move these constants to a common header file
#define MAX_DAMAGE 25
#define MAX_PURCHASE_POINTS 999
#define PURCHASE_POINTS_INC 15

struct Player {
  size_t purchasePoints;
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
  /// @throws std::runtime_error if the galaxy could not be created
  void startGame(const char* galaxyFileDirectory);

  /// @brief Uses a probing vessel to explore solar system planets
  /// @param vesselID ID of the vessel to be used in the probe
  /// @param startPlanet coordinates of the planet where the probe starts
  void probe(size_t vesselID, Coordinates& startPlanet);

  /// @brief Uses a scouting vessel to explore solar system paths
  /// @param vesselID ID of the vessel to be used in the scout
  /// @param startPlanet coordinates of the planet where the scout starts
  void scout(size_t vesselID, Coordinates& startPlanet);

  /// @brief Sends an attack to a planet
  /// @param vesselID ID of the vessel to be used in the attack
  /// @param startPlanet coordinates of the planet where the attack starts
  /// @param targetPlanet coordinates of the planet to be attacked
  /// @return the result of the attack
  size_t attack(size_t vesselID, Coordinates& startPlanet
    , Coordinates& targetPlanet);

  /// Collects purchase points based on the number of active mines
  void collectPurchasePoints();

  /// @brief Tries to consume purchase points if there is enough
  /// @param points number of purchase points to consume
  /// @return true on success, false if not enough points
  bool consumePurchasePoints(size_t points);

  /**
   * @brief checks if the game is over
   * @return true is game is over
   */
  bool isGameOver();

  /// @brief Getters
  Galaxy* getGalaxy() const;
  BattleLog* getBattleLog() const;
  VesselsCollection<Planet*, size_t>& getVessels();
  /// @brief get player's purchase points
  size_t getPurchasePoints();
};
