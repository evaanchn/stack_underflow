// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>

#include "Algorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Breadth first search algorithm over a graph
 */
template <typename DataType, typename WeightType>
class BFS : public Algorithm<DataType, WeightType> {
 public:
  /// Constructor
  BFS() {
    this->algorithmName = "BFS";
  }
  /**
   * @brief Explore new nodes and add them to their corresponding container
   * 
   * @param startingNode bfs starting point
   * @param adjacencyList read only map with available edges from each node
   * @param exploredElements explored Node.data elements container
   * @param limit exploration limit
   * @return int EXIT_SUCCESS or EXIT_FAILURE
   */
  int explore(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_set<DataType>& exploredElements, const size_t limit) {
    // whenever the graph elements are not fully explored
    if (exploredElements.size() < adjacencyList.size()) {
      // update all new elements found by the algorithm
      for (auto& explored : this->breadthFirstSearch(startingNode, adjacencyList
          , limit)) {
        exploredElements.insert(explored);
      }
    }
    return EXIT_SUCCESS;
  }
  /**
   * @brief Breadth first search algorithm, bounded
   * 
   * @param startingNode first element to visit
   * @param adjacencyList read only map with available edges from each node
   * @param limit max number of elements to visit
   * @return std::unordered_set<DataType> visited container, no order
   */
  std::unordered_set<DataType> breadthFirstSearch(Node<DataType>* startingNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , const size_t limit = SIZE_MAX) {
    // first_in-first_out queue
    std::queue<Node<DataType>*> visitingNodes;
    // visited control
    std::unordered_set<DataType> visitedElements;
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
          if (visitedElements.size() > limit) return visitedElements;
        }
      }
    }
    return visitedElements;
  }
};
