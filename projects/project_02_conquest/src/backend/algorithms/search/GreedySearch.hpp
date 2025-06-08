// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

  /// @brief Greedy Search: always follows the locally cheapest edge
  /// until reaching a previously explored node
  /// @param startNode first element to visit
  /// @param endNode Goal node
  /// @param adjacencyList read only map with available edges from each node
  /// @param nodeIndexes Map nodes to their assigned index
  /// @param validEdges matrix to check if an edge is accesible
  /// @param totalWeight total weight of the attack
  /// @return size_t iterations taken
  size_t attack(Node<DataType>* startNode, Node<DataType>* endNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_map<Node<DataType>*, size_t>& nodeIndexes
      , std::vector<std::vector<bool>>& validEdges, WeightType& totalWeight)
      override {
    // map to save the used edges and their accumulated weight
    std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>> usedEdges;
    // perform the greedy search
    return greedy(startNode, endNode, adjacencyList, nodeIndexes, validEdges
      , totalWeight, usedEdges);
  }
  /// @brief Performs a greedy search saving the used edges accumulated weight
  /// @param startNode search begin
  /// @param endNode objective node to reach
  /// @param adjacencyList read only map with available edges from each node
  /// @param nodeIndexes Map nodes to their assigned index
  /// @param validEdges matrix to check if an edge is accesible
  /// @param totalWeight total weight of the attack
  /// @param usedEgdes map to save the used edges and their accumulated weight
  /// @return iterations taken
  static size_t greedy(Node<DataType>* startNode, Node<DataType>* endNode,
      const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_map<Node<DataType>*, size_t>& nodeIndexes
      , std::vector<std::vector<bool>>& validEdges, WeightType& totalWeight
      , std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& usedEgdes) {
    // iterations taken by the algorithm
    size_t iterations = 0;
    totalWeight = 0;  // reset total weight for the actual search
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
      WeightType minWeight = defaultNoEdge<WeightType>();
      // Pick the cheapest edge to an unvisited neighbor
      for (const auto& [neighbor, weight] : neighbors) {
        // Check if the edge is valid or neighbor has been visited
        if (!(validEdges[nodeIndexes[current]][nodeIndexes[neighbor]])
          || visited.find(neighbor->getData()) != visited.end()) {
          continue;  // skip invalid edges
        }
        // Explore all the neigbors to get the cheapest one
        if (weight < minWeight) {
          // if the neighbor has not been visited and the weight is lower than
          // the current minimum weight, update the next node
          minWeight = weight;
          nextNode = neighbor;
        }
      }
      if (nextNode == nullptr) {
        // stops when there is no available neighbors
        break;
      }
      // add the minimum weight to the total weight
      totalWeight += minWeight;
      // set both directions of the edge as used with the accumulated weight
      usedEgdes[current][nextNode] = totalWeight;
      usedEgdes[nextNode][current] = totalWeight;
      current = nextNode;
      visited.insert(current->getData());
      ++iterations;
    }
    if (current != endNode) {
      // if exit the loop without having reached the end Node, no path was found
      totalWeight = defaultNoEdge<WeightType>();
    }
    return iterations;
  }
};
