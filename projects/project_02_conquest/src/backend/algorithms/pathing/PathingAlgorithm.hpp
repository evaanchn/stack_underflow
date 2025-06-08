// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Algorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Shortest path finding algorithm over a graph
 */
template <typename DataType, typename WeightType>
class PathingAlgorithm : public Algorithm<DataType, WeightType> {
 public:
  /// Constructor
  PathingAlgorithm() = default;

  /// Update index inside the validEdges matrix for the last edge set as valid
  /// for the given node.
  /// @param validEdges matrix to set shortest path edges as valid
  /// @param distances vector of pairs with distance and adyacent index
  /// @param nodeIndex index of the node to update
  /// @param valid set edge as valid or not
  /// @param directed if the graph is directed or not
  /// @throws std::out_of_range
  void updateEdgeIndex(std::vector<std::vector<bool>>& validEdges
      , const size_t adjacentIndex
      , const size_t nodeIndex, const bool valid, const bool directed = false) {
    try {
      // validEdges[node][last adjacent]
      validEdges.at(nodeIndex).at(adjacentIndex) = valid;
      if (directed) return;  // update only one direction if directed
      // validEdges[last adjacent conected to node][node]
      validEdges.at(adjacentIndex).at(nodeIndex) = valid;
    } catch(const std::out_of_range& error) {
      throw std::out_of_range("Invalid edge index in updateEdgeIndex");
    }
  }
   /**
   * @brief Set as valid the edges of the algorithm shortest path
   * 
   * @param graph Graph to perform pathing algorithm upon
   * @param discoveredElements reachable node elements container
   * @param validEdges matrix to set shortest path edges as valid
   * @param startingNode starting point (pivot)
   * @return size_t iterations taken
   */
  virtual size_t route(Graph<DataType, WeightType>* graph
    , const std::unordered_set<DataType>& discoveredElements
    , std::vector<std::vector<bool>>& validEdges
    , Node<DataType>* startingNode = nullptr) = 0;
};
