// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define ELEMENT_COUNT 50
#define MAX_DAMAGE (ELEMENT_COUNT * 2)

class Vessel {
 public:
  // Constructor
  Vessel(std::string nameInit, int64_t healthInit, size_t costInit
      , size_t weightInit);

  /**
   * @brief Search given key
   * 
   * @param value key
   * @param log to register operation time and iterations
   * @return int iterations taken
   */
  int search(int value/*, ActionLog& log*/);

  /**
   * @brief Insert given key
   * 
   * @param value key
   * @param log to register operation time and iterations
   * @return int iterations taken
   */
  int insert(int value/*, ActionLog& log*/);  
  
   /**
   * @brief Remove given key
   * 
   * @param value key
   * @param upgrade_points maximum iterations possible
   * @param log to register operation time and iterations
   * @return int iterations taken
   */
  int Vessel::deletion(int value, size_t& upgrade_points/*, ActionLog& log*/);

  /**
   * @brief Fill vessel data structure with random values
   * @details to be called after a vessel is created
   * 
   * @param logs to register insetions time and iterations
   * @return int iterations taken
   */
  void fillVessel(/*std::vector<ActionLog>& logs*/);

  /**
   * @brief Checks the health to be above 0
   * 
   * @return true: health <= 0
   * @return false: health > 0 
   */
  bool isAlive();

  /**
   * @brief Obtain the damage value by doing a search on its data of a
   * random number
   * 
   * @return int damage to be dealt
   */
  int calculateDamage();

  /**
   * @brief Decrease the health value of the vessel with a valid amount of
   * damage
   * 
   * @param damageDealT
   */
  void takeDamage(int64_t damageDealt);

 protected:
  /*Algorithm algorithm*/
  std::string name;
  int64_t health = 0;
  size_t cost = 0;
  size_t weight = 0;
};
