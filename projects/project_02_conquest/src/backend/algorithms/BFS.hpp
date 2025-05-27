// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>

#include "TraversalAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Breadth first search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class BFS : public TraversalAlgorithm<DataType, WeightType> {
 public:
  /// Constructor
  BFS() {
    this->algorithmName = "BFS";
  }

  /**
   * @brief Breadth first search algorithm, bounded
   * 
   * @param startingNode first element to visit
   * @param adjacencyList read only map with available edges from each node
      * @param visitedElements container reference to store visited elements
   * @param limit max number of elements to visit
   * @return size_t iterations taken
   */
  size_t traverse(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& visitedElements
      , const size_t limit = SIZE_MAX) override {
    // iterations taken by the algorithm
    size_t iterations = 0;
    // first_in-first_out queue
    std::queue<Node<DataType>*> visitingNodes;
    // starting node into visiting queue
    visitingNodes.push(startingNode);
    // stating node as visited
    visitedElements.insert(startingNode->getData());
    while ((!visitingNodes.empty())) {
      // dequeue node to visit its adjacents
      Node<DataType>* actual = visitingNodes.front();
      visitingNodes.pop();
      // traverse adjacent nodes adding them to the queue
      for (auto& adjacent : adjacencyList.at(actual)) {
        // avoid revisiting explored nodes
        if ((visitedElements.find(adjacent.first->getData())
            == visitedElements.end())) {
          // set node element as visited
          visitedElements.insert(adjacent.first->getData());
          // enqueue node for adjacents visiting
          visitingNodes.push(adjacent.first);
          // stop if the visited limited was reached (size = limit + start)
          if (visitedElements.size() > limit) return iterations;
        }
        ++iterations;  // for each adyacent from actual node
      }
    }
    return iterations;
  }
};
