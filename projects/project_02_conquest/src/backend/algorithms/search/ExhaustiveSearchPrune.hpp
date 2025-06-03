// Copyright 2025 stack_underflow CC-BY 4.0

// external sources:
// Copyright (c) 2024 Geeks for Geeks:
// https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/

#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ExhaustiveSearch.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Exhaustive search prune algorithm over a graph
 */
template <typename DataType, typename WeightType>
class ExhaustiveSearchPrune: public ExhaustiveSearch<DataType, WeightType> {
 public:
  /// @brief Constructor of the class
  ExhaustiveSearchPrune() {
    this->algorithmName = "Exhaustive Search Prune";
  }

  /**
   * @brief Exhaustive Search: evaluate all possible paths until find the best
   *        one in the graph
   *
   * @param startNode first element to visit
   * @param endNode Goal node
   * @param adjacencyList read only map with available edges from each node
   * @param totalWeight total weight of the attack
   * @return size_t iterations taken
   */
  size_t attack(Node<DataType>* startNode, Node<DataType>* endNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , WeightType& totalWeight) override {
    // total weight initialization
    totalWeight = std::numeric_limits<WeightType>::max();
    // iterations taken by the algorithm
    size_t iterations = 0;
    // container to store visited elements in actual traversal
    std::unordered_set<Node<DataType>*> visited;
    this->findMinPath(startNode, endNode, visited, adjacencyList
        , static_cast<WeightType>(0), totalWeight, iterations, true);
    // validates if no path was found
    if (totalWeight == std::numeric_limits<WeightType>::max()) {
      totalWeight = 0;
    }
    return iterations;
  }
};
