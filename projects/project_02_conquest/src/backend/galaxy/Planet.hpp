// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <math.h>
#include <string>

#include "Boss.hpp"
#include "Coordinates.hpp"

#define HAS_MINE true
#define EMPTY_STRING ""

class Planet {
 private:
  std::string name = EMPTY_STRING;
  bool planetHasMine = !HAS_MINE;
  Boss* boss = nullptr;
  Coordinates* coordinates = nullptr;

 public:
  /// @brief Default constructor for the Planet class.
  Planet() = default;

  /**
   * @brief Constructor with attributes.
   * @param name Name of the planet.
   * @param planetHasMine Indicates whether the planet contains a mine.
   * @param boss Pointer to a Boss object (optional).
   * @param coordinates Pointer to a Coordinates object (optional).
   */
  Planet(std::string name, bool planetHasMine, Boss* boss = nullptr
      , Coordinates* coordinates = nullptr);

  /// @brief Destructor for the Planet class.
  ~Planet();

  /**
   * @brief Sets the coordinates of the planet.
   * @param coordinates Pointer to a Coordinates object.
   */
  void setCoordinates(Coordinates* coordinates);

  /// @brief Spawns a boss on the planet.
  void spawnBoss();

  /// @brief Defeats the boss on the planet.
  void defeatBoss();

  /**
   * @brief Checks whether the planet currently has a boss.
   * @return True if the planet has a boss, false otherwise.
   */
  bool hasBoss() const;

  /**
   * @brief Checks whether the planet has a mine.
   * @return True if the planet has a mine, false otherwise.
   */
  bool hasMine() const;

  /**
   * @brief Gets the pointer to the boss on the planet.
   * @return Pointer to a Boss object.
   */
  Boss* getBoss();

  /**
   * @brief Gets the name of the planet.
   * @return Name of the planet as a std::string.
   */
  std::string getName() const;

  /**
   * @brief Gets the coordinates of the planet.
   * @return Pointer to a Coordinates object.
   */
  Coordinates* getCoordinates() const;

  /**
   * @brief Returns a string representation of the planet.
   * @return A std::string describing the planet.
   */
  std::string toString() const;

  /**
   * @brief Calculates distance to another planet based on coordinates.
   * @param otherPlanet Other planet to calculate distance to.
   * @return Distance in floating point.
   */
  double getDistanceTo(Planet* otherPlanet);
};

/**
 * @struct PlanetPtrHash
 * @brief Custom hash function for using Planet* as keys
 * in unordered containers.
 */
struct PlanetPtrHash {
  /**
   * @brief Computes a hash value for a Planet* using the planet's name.
   * @param planet Pointer to a Planet object.
   * @return Hash value based on the planet's name.
   */
  std::size_t operator()(const Planet* planet) const {
    return std::hash<std::string>()(planet->getName());
  }
};
