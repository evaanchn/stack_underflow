// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

/**
 * @brief General class template for algorithms
 */
class Algorithm {
 protected:
  std::string algorithmName = " ";

 public:
  /// @brief constructor method of the algorithm class
  Algorithm();
  /// @brief destructor method of the algorithm class
  virtual ~Algorithm();
  /**
   * @brief Get name attribute
   * 
   * @return std::string 
   */
  std::string getName();
};
