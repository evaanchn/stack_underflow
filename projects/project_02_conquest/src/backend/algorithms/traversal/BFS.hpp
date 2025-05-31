// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>

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
   * @param discoveredElements container reference to store discovered elements
   * @param limit max number of nodes to visit
   * @return size_t iterations taken
   */
  size_t traverse(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& discoveredElements
      , size_t limit = SIZE_MAX) override {
    // iterations taken by the algorithm
    size_t iterations = 0;
    // first_in-first_out queue
    std::queue<Node<DataType>*> visitingNodes;
    // container to store visited elements in actual traversal
    std::unordered_set<DataType> visitedActual;
    // starting node into visiting queue
    visitingNodes.push(startingNode);
    // stating node as visited
    discoveredElements.insert(startingNode->getData());
    while ((!visitingNodes.empty())) {
      // dequeue node to visit its adjacents
      Node<DataType>* actual = visitingNodes.front();
      visitingNodes.pop();
      // if the element was never visited before
      if ((discoveredElements.find(actual->getData())
        == discoveredElements.end())) {
        discoveredElements.insert(actual->getData());
        // one less element to discover
        --limit;
        // stop if the discover limit was reached
        if (limit == 0) return iterations;
      }
      // traverse adjacent nodes adding them to the queue
      for (auto& adjacent : adjacencyList.at(actual)) {
        ++iterations;  // for each adyacent from actual node
        // avoid revisiting explored nodes
        if ((visitedActual.find(adjacent.first->getData())
            == visitedActual.end())) {
          // set as visited in this traversal
          visitedActual.insert(adjacent.first->getData());
          // enqueue node for adjacents visiting
          visitingNodes.push(adjacent.first);
          
        }
      }
    }
    return iterations;
  }
};
