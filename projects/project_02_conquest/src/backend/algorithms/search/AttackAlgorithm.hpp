// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>

#include "Algorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Greedy search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class AttackAlgorithm : public Algorithm<DataType, WeightType> {
 public:
  /// Constructor
  AttackAlgorithm() = default;

  /**
   * @brief Attack type algorithm
   * 
   * @param startNode first element to visit
   * @param endNode Goal node
   * @param adjacencyList read only map with available edges from each node
   * @param totalWeight total weight of the attack
   * @return size_t iterations taken
   */
  virtual size_t attack(
      Node<DataType>* startingNode, Node<DataType>* endNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList,
      size_t& totalWeight) = 0;
};
