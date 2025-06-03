// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <iostream>

#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <vector>

#include "PathingAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Floyd algorithm over a graph, with modifications O(V^3)
 */
template <typename DataType, typename WeightType>
class Floyd : public PathingAlgorithm<DataType, WeightType> {
 public:
  /// Constructor
  Floyd() {
    this->algorithmName = "Floyd";
  }
  /**
   * @brief Set as valid the shortest path from startingNode to
   * all other explored nodes
   * 
   * @param graph Graph to try
   * @param discoveredElements reachable node elements container
   * @param validEdges matrix to set shortest path edges as valid
   * @param startingNode starting pointer (pivot)
   * @return size_t iterations taken
   */
  size_t route(Graph<DataType, WeightType>* graph
    , const std::unordered_set<DataType>& discoveredElements
    , std::vector<std::vector<bool>>& validEdges
    , Node<DataType>* startingNode = nullptr) override {
    (void) startingNode;  // Starting node is unused
    // Get adjacency matrix from graph
    std::vector<std::vector<WeightType>>& adjacencyMatrix
        = graph->getAdjacencyMatrix();
    // Get graph's nodes record
    std::vector<Node<DataType>*>& nodes = graph->getNodes();
    // Make a deep copy of the adjacency matrix
    std::vector<std::vector<WeightType>> weightsMatrix = adjacencyMatrix;

    size_t nodesAmount = weightsMatrix.size();
    size_t iterations = 0;
    // Intermediate node -> iterates through all nodes
    for (size_t intermediate = 0; intermediate < nodesAmount; ++intermediate) {
      // If intermediate has data in the discovered elements, don't consider it
      if (discoveredElements.find(nodes[intermediate]->getData())
            == discoveredElements.end()) continue;
      // Iterate through connections
      for (size_t fromNode = 0; fromNode < nodesAmount; ++fromNode) {
        // If current node does not contain a discovered element, skip
        if (discoveredElements.find(nodes[fromNode]->getData())
            == discoveredElements.end()) continue;
        for (size_t toNode = 0; toNode < nodesAmount; ++toNode) {
          // If to node does not contain a discovered element, skip
          // Or if the connection is from node to itself
          if (discoveredElements.find(nodes[toNode]->getData())
              == discoveredElements.end() || fromNode == toNode) continue;
          // If weight to intermediate or from intermediate to node is infinite
          // If path from current node to intermediate to destination is shorter
          if (weightsMatrix[fromNode][intermediate]
              != defaultNoEdge<WeightType>()
              && weightsMatrix[intermediate][toNode]
              != defaultNoEdge<WeightType>()
              && weightsMatrix[fromNode][intermediate]
              + weightsMatrix[intermediate][toNode]
              < weightsMatrix[fromNode][toNode]) {
            // Update shorter path in weight matrix
            weightsMatrix[fromNode][toNode]
                = weightsMatrix[fromNode][intermediate]
                + weightsMatrix[intermediate][toNode];
            // If there is an edge from node to intermediate, mark as valid
            if (adjacencyMatrix[fromNode][intermediate]
                != defaultNoEdge<WeightType>())
                validEdges[fromNode][intermediate] = true;
            // If there is an edge from intermediate to node, mark as valid
            if (adjacencyMatrix[intermediate][toNode]
                != defaultNoEdge<WeightType>())
                validEdges[intermediate][toNode] = true;
          }
          ++iterations;
        }
      }
    }
    return iterations;
  }
};
