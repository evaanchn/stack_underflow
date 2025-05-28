// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "Algorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Greedy algorithm over a graph
 */
template <typename DataType, typename WeightType>
class GreedySearch : public Algorithm<DataType, WeightType> {
 public:
  /// @brief Constructor of the class
  GreedySearch() {
    this->algorithmName = "Greedy";
  }

  /// Destructor of the class
  ~GreedySearch() {}

  /**
   * @brief
   */
  int64_t explore();

  /**
   * @brief Greedy search algorithm
   * @param startingNode first element to visit
   * @param adjacencyList read only map with available edges from each node
   * @param limit max number of elements to visit
   * @return std::unordered_set<DataType> visited container, no order
   */
  std::unordered_set<DataType> breadthFirstSearch(Node<DataType>* startingNode
    , const std::unordered_map<Node<DataType>*
    , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
    , const size_t limit = SIZE_MAX) {
  }
};
