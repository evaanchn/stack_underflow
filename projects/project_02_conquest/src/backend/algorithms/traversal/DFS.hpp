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
   * @param visitedElements container reference to store visited elements
   * @param limit max number of nodes to visit
   * @return size_t iterations taken
   */
  size_t traverse(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& visitedElements
      , const size_t limit = SIZE_MAX) override {
    // iterations taken by the algorithm
    size_t iterations = 0;
    // first-in-last-out stack
    std::stack<Node<DataType>*> visitingNodes;
    // starting node into visiting stack
    visitingNodes.push(startingNode);
    // stating node as visited
    visitedElements.insert(startingNode->getData());
    while ((!visitingNodes.empty())) {
      // Pop node from stack
      Node<DataType>* actual = visitingNodes.top();
      visitingNodes.pop();

      // Determine if current node has been visited
      if (visitedElements.find(actual->getData())
            == visitedElements.end()) {
        // set node element as visited
        visitedElements.insert(actual->getData());
        // stop if the visited limited has reached (size = limit + start)
        if (visitedElements.size() > limit) return iterations;
        ++iterations;  // Record visit to node as iteration
      }

      // Traverse adjacent nodes and pish them into the stack
      for (auto& adjacent : adjacencyList.at(actual)) {
        // avoid revisiting explored nodes
        if ((visitedElements.find(adjacent.first->getData())
            == visitedElements.end())) {
          // Push node into stack for adjacents visiting
          visitingNodes.push(adjacent.first);
        }
      }
    }

    return iterations;
  }
};
