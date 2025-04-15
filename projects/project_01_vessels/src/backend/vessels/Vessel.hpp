// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Algorithm.hpp"
#include "BattleLog.hpp"

#define ELEMENT_COUNT 50
#define MAX_DAMAGE (ELEMENT_COUNT * 2)

class Vessel {
 public:
  /// Constructor
  explicit Vessel(std::string nameInit, int64_t healthInit, size_t costInit
      , size_t weightInit);
  virtual ~Vessel();

  /**
   * @brief Search given key
   * 
   * @param value key
   * @param log to register operation time and iterations
   * @return size_t iterations taken
   */
  size_t search(int64_t element, ActionLog& log);

  /**
   * @brief Insert given key
   * 
   * @param value key
   * @param log to register operation time and iterations
   * @return size_t iterations taken
   */
  size_t insert(int64_t element, ActionLog& log);

   /**
   * @brief Remove given key
   * 
   * @param value key
   * @param upgrade_points maximum iterations possible
   * @param log to register operation time and iterations
   * @return size_t iterations taken
   */
  size_t deletion(int64_t element, ActionLog& log);

  /**
   * @brief Fill vessel data structure with random values
   * @details to be called after a vessel is created
   * 
   * @param logs to register insetions time and iterations
   */
  virtual void fillVessel(std::vector<ActionLog>& logs);

  /**
   * @brief Checks the health to be above 0
   * 
   * @return true: health <= 0
   * @return false: health > 0 
   */
  bool isAlive();

  size_t getWeight();
  size_t getCost();

  /**
   * @brief Obtain the damage value by doing a search on its data of a
   * random number
   * 
   * @return int damage to be dealt
   */
  int calculateDamage(ActionLog& log);

  /**
   * @brief Decrease the health value of the vessel with a valid amount of
   * damage
   * 
   * @param damageDealT
   */
  void takeDamage(int64_t damageDealt);

  /**
   * @brief Try to eliminate elements from the vessel
   * 
   * @param upgradePoints maximum number of iterations
   * @return true success
   * @return false failure
   */
  bool upgradeVessel(const size_t upgradePoints, std::vector<ActionLog>& logs);

 protected:
  void shuffle(std::vector<int> numbers);
  int64_t randValue(int64_t min, int64_t max);

 protected:
  Algorithm* algorithm;
  std::string name;
  int64_t health;
  size_t cost;
  size_t weight;
};
