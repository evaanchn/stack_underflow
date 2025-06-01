// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>

#include "Algorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Traversal type algorithm over a graph
 */
template <typename DataType, typename WeightType>
class TraversalAlgorithm : public Algorithm<DataType, WeightType> {
 public:
  /// Constructor
  TraversalAlgorithm() = default;

  /**
   * @brief Traverse type algorithm, bounded
   * 
   * @param startingNode first element to visit
   * @param adjacencyList read only map with available edges from each node
   * @param discoveredElements container reference to store discovered elements
   * @param limit max number of elements to visit
   * @return size_t iterations taken
   */
  virtual size_t traverse(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& discoveredElements
      , const size_t limit = SIZE_MAX) = 0;
};
