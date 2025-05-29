// Copyright 2025 stack_underflow CC-BY 4.0

// external sources:
// Copyright (c) 2024 Geeks for Geeks:
// https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/

#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
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
    this->algorithmName = "Exhaustive";
  }

  /**
   * @brief Exhaustive Search: always follows the locally cheapest edge
   *        until reaching a previously explored node
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
      , size_t& totalWeight) override {
    totalWeight = std::numeric_limits<WeightType>::max();
    size_t iterations = 0;
    // Collect all nodes except start for permutation
    std::vector<Node<DataType>*> nodes;
    for (const auto& [node, neighbors] : adjacencyList) {
      if (node != startNode) {
        nodes.push_back(node);
      }
    }
    // Try all permutations of paths
    while (std::next_permutation(nodes.begin(), nodes.end())) {
      WeightType currentWeight = 0;
      Node<DataType>* currentNode = startNode;
      bool validPath = true;
      // Follow the current permutation
      for (Node<DataType>* nextNode : nodes) {
        iterations++;
        // Check if edge exists
        if (adjacencyList.at(currentNode).count(nextNode) == 0) {
          validPath = false;
          break;
        }
        currentWeight += adjacencyList.at(currentNode).at(nextNode);
        // Early exit if path is already worse than the best
        if (currentWeight >= totalWeight) {
          validPath = false;
          break;
        }
        currentNode = nextNode;
        // Stop if reached the end node
        if (currentNode == endNode) {
          break;
        }
      }
      // Update best weight if this path is valid and better
      if (validPath && currentNode == endNode &&
          currentWeight < totalWeight) {
        totalWeight = currentWeight;
      }
    }
    // If no path found, return 0
    if (totalWeight == std::numeric_limits<WeightType>::max()) {
      totalWeight = 0;
    }
    return iterations;
  }
};
