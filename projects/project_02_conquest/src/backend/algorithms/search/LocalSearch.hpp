// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AttackAlgorithm.hpp"
#include "Graph.hpp"
#include "GreedySearch.hpp"
#include "Node.hpp"

// TODO(any): make this a parameter
#define LOCAL_OPTIMIZATION_LIMIT 2

/**
 * @brief Loclal search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class LocalSearch : public AttackAlgorithm<DataType, WeightType> {
 public:
  /// @brief Constructor of the class
  LocalSearch() {
    this->algorithmName = "Local Search";
  }

  /**
   * @brief Local Search: 
   *
   * @param startNode first element to visit
   * @param endNode Goal node
   * @param adjacencyList read only map with available edges from each node
   * @param nodeIndexes Map nodes to their assigned index
   * @param validEdges matrix to check if an edge is accesible
   * @param totalWeight total weight of the attack
   * @return size_t iterations taken
   */
  size_t attack(Node<DataType>* startNode, Node<DataType>* endNode,
      const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList,
      std::unordered_map<Node<DataType>*, size_t>& nodeIndexes,
      std::vector<std::vector<bool>>& validEdges,
      WeightType& totalWeight) override {

    size_t iterations = 0;
    WeightType bestWeight = std::numeric_limits<WeightType>::max();
    bool pathFound = false;

    // Used edge map shared between greedy and local search
    std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>> usedEdges;

    // Run greedy to get an initial solution
    WeightType initialWeight = 0;
    size_t greedyIters = GreedySearch<DataType, WeightType>::greedy(
        startNode, endNode, adjacencyList, nodeIndexes,
        validEdges, initialWeight, usedEdges);
    iterations += greedyIters;

    if (initialWeight > 0) {
      bestWeight = initialWeight;
      pathFound = true;
    }

    // Attempt to improve the path using local search
    for (size_t optimization = 0; optimization < LOCAL_OPTIMIZATION_LIMIT; ++optimization) {
      WeightType attemptWeight = 0;
      size_t localIters = localSearch(startNode, endNode, adjacencyList, nodeIndexes,
                                      validEdges, attemptWeight, usedEdges);
      iterations += localIters;

      if (attemptWeight > 0 && attemptWeight < bestWeight) {
        bestWeight = attemptWeight;
        pathFound = true;
      }
    }

    // Set the final weight
    totalWeight = pathFound ? bestWeight : 0;
    return iterations;
  }

  /// @brief Performs a search taking different paths by avoiding used edges
  /// @param startNode search begin
  /// @param endNode objective node to reach
  /// @param adjacencyList read only map with available edges from each node
  /// @param nodeIndexes Map nodes to their assigned index
  /// @param validEdges matrix to check if an edge is accesible
  /// @param totalWeight total weight of the attack
  /// @param usedEgdes map to save the used edges and their accumulated weight
  /// @return iterations taken
  static size_t localSearch(Node<DataType>* startNode, Node<DataType>* endNode,
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
      WeightType minWeight = std::numeric_limits<WeightType>::max();
      // Pick the cheapest edge to an unvisited neighbor
      for (const auto& [neighbor, weight] : neighbors) {
        // Check if the edge is valid or neighbor has been visited
        if (!(validEdges[nodeIndexes[current]][nodeIndexes[neighbor]])
            || visited.find(neighbor->getData()) != visited.end()) {
          continue;  // skip invalid edges
        }
        // Explore all neigbors to get the cheapest one
        if (weight < minWeight) {
          // Check if the edge has been used and there is other unused edges
          if (usedEgdes[current].count(neighbor) > 0
              && neighbors.size() > usedEgdes[current].size()) {
            continue;
          }
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
      totalWeight = 0;
    }
    return iterations;
  }
};
