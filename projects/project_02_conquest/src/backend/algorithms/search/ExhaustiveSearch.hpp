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

#include "AttackAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Exhaustive search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class ExhaustiveSearch : public AttackAlgorithm<DataType, WeightType> {
 public:
  /// @brief Constructor of the class
  ExhaustiveSearch() {
    this->algorithmName = "Exhaustive Search";
  }

  /**
   * @brief Recursively explores possible paths from current node to and bound
   *        destination while tracking the minimum path weight found.
   *
   * @param currentNode Node being currently visited in the search
   * @param destiny Target node to reach
   * @param visited Set of already visited nodes to avoid cycles
   * @param adjacencyList Graph's adjacency list representation
   * @param currentWeight Accumulated weight of the current path
   * @param minWeight Reference to store the minimum weight found
   * @param iterations Counter of recursive calls (performance metric)
   * @param prune if prune == true, punes all unnecesary paths
   */
  void findMinPath(Node<DataType>* currentNode, Node<DataType>* destiny
      , std::unordered_set<Node<DataType>*>& visited
      , const std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , WeightType currentWeight, WeightType& minWeight, size_t& iterations
      , bool prune) {
    iterations++;
    // if we find destiny, compare weights
    if (currentNode == destiny) {
      if (currentWeight < minWeight) {
        minWeight = currentWeight;
      }
      return;
    }
    // mark current node as visited
    visited.insert(currentNode);
    // explore all the neigbors
    const auto& neighbors = adjacencyList.at(currentNode);
    for (const auto& neighborPair : neighbors) {
      Node<DataType>* neighbor = neighborPair.first;
      // check if node has not been visited
      if (visited.find(neighbor) == visited.end()) {
        WeightType edgeWeight = neighborPair.second;
        // verifies Exhaustive Search version
        if (prune) {
          // cut branches if the current weight is exceeded
          if (currentWeight + edgeWeight < minWeight) {
            findMinPath(neighbor, destiny, visited, adjacencyList
                , currentWeight + edgeWeight, minWeight, iterations, prune);
          }
        } else {
          findMinPath(neighbor, destiny, visited, adjacencyList
              , currentWeight + edgeWeight, minWeight, iterations, prune);
        }
      }
    }
    // go back and unmark the current node to probe other possible paths
    visited.erase(currentNode);
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
    findMinPath(startNode, endNode, visited, adjacencyList
        , static_cast<WeightType>(0), totalWeight, iterations, false);
    // validates if no path was found
    if (totalWeight == std::numeric_limits<WeightType>::max()) {
      totalWeight = 0;
    }
    return iterations;
  }
};
