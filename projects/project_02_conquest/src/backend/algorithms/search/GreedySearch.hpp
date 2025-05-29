// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "AttackAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Greedy search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class GreedySearch : public AttackAlgorithm<DataType, WeightType> {
 public:
  /// @brief Constructor of the class
  GreedySearch() {
    this->algorithmName = "Greedy";
  }

  /**
   * @brief Greedy Search: always follows the locally cheapest edge
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
    // iterations taken by the algorithm
    size_t iterations = 0;
    // set used for saving visited nodes
    std::unordered_set<DataType> visited;
    // starts with startNode
    Node<DataType>* current = startNode;
    visited.insert(current->getData());
    while (current != endNode) {
      // gets all the neighbors of the current node
      const auto& neighbors = adjacencyList.at(current);
      Node<DataType>* nextNode = nullptr;
      // Variable to keep track of the minimum weight
      WeightType minWeight = std::numeric_limits<WeightType>::max();
      // Pick the cheapest edge to an unvisited neighbor
      for (const auto& [neighbor, weight] : neighbors) {
        ++iterations;
        // Explore all the neigbors to get the cheapest one
        if (visited.count(neighbor->getData()) == 0 && weight < minWeight) {
          minWeight = weight;
          nextNode = neighbor;
        }
      }
      if (nextNode == nullptr) {
        // stops when there is no available neighbors
        break;
      }
      // move along that edge
      totalWeight += minWeight;
      current = nextNode;
      visited.insert(current->getData());
    }
    return iterations;
  }
};
