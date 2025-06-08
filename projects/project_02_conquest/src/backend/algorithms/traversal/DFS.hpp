// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "TraversalAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Depth first search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class DFS : public TraversalAlgorithm<DataType, WeightType> {
 public:
  /// Constructor
  DFS() {
    this->algorithmName = "DFS";
  }

  /**
   * @brief Depth first search algorithm, bounded
   * 
   * @param startingNode first element to visit
   * @param adjacencyList read only map with available edges from each node
   * @param discoveredElements container reference to store discovered elements
   * @param limit max number of nodes to visit
   * @return size_t iterations taken
   */
  size_t traverse(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& discoveredElements
      , size_t limit = SIZE_MAX) override {
    // container to store visited elements in actual traversal
    std::unordered_set<DataType> visitedActual;
    // iterations taken by the algorithm
    size_t iterations = 0;
    // first-in-last-out stack
    std::stack<Node<DataType>*> visitingNodes;
    // starting node into visiting stack
    visitingNodes.push(startingNode);
    // stating node as visited
    visitedActual.insert(startingNode->getData());
    while ((!visitingNodes.empty())) {
      // Pop node from stack
      Node<DataType>* actual = visitingNodes.top();
      visitingNodes.pop();
      ++iterations;  // Record visited nodes as an iteration
      // Determine if current node has been discovered before
      if (discoveredElements.find(actual->getData())
            == discoveredElements.end()) {
        // one less element to discover
        --limit;
        // set node element as visited
        discoveredElements.insert(actual->getData());
        // stop if the discover limit was reached
        if (limit == 0) return iterations;
      }

      // Traverse adjacent nodes and pish them into the stack
      for (auto& adjacent : adjacencyList.at(actual)) {
        // avoid revisiting explored nodes
        if ((visitedActual.find(adjacent.first->getData())
            == visitedActual.end())) {
          // set as visited in this traversal
          visitedActual.insert(adjacent.first->getData());
          // Push node into stack for adjacents visiting
          visitingNodes.push(adjacent.first);
        }
      }
    }

    return iterations;
  }
};
