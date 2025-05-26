// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

/**
 * @brief General class template for graph traversal algorithms
 * @tparam DataType type stored in the nodes.
 * @tparam WeightType type used for edge weights.
 */
template <typename DataType, typename WeightType>
class Algorithm {
 protected:
  std::string algorithmName = " ";

 public:
  /// @brief constructor method of the algorithm class
  Algorithm() = default;
  /// @brief destructor method of the algorithm class
  virtual ~Algorithm() = default;
  /**
   * @brief Get name attribute
   * 
   * @return std::string 
   */
  std::string getName() {
    return this->algorithmName;
  }
};
