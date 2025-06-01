// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <vector>

#include "PathingAlgorithm.hpp"
#include "Graph.hpp"
#include "Node.hpp"

/**
 * @brief Dijkstra algorithm over a graph
 */
template <typename DataType, typename WeightType>
class Dijkstra : public PathingAlgorithm<DataType, WeightType> {
 public:
  /// Constructor
  Dijkstra() {
    this->algorithmName = "Dijkstra";
  }
  /**
   * @brief Set as valid the shortest path from startingNode to
   * all other explored nodes
   * 
   * @param startingNode starting pointer (pivot)
   * @param adjacencyList read only map with available edges from each node
   * @param discoveredElements reachable node elements container
   * @param nodeIndexes Map nodes to their assigned index
   * @param validEdges matrix to set shortest path edges as valid
   * @return size_t iterations taken
   */
  size_t route(Node<DataType>* startingNode
    , const std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
    , const std::unordered_set<DataType>& discoveredElements
    , std::unordered_map<Node<DataType>*, size_t>& nodeIndexes
    , std::vector<std::vector<bool>>& validEdges)  override {

    size_t iterations = 0;
    // priority queue to visit nodes in order of their distance
    // <comparison DataType, elements container, comparator>
    std::priority_queue<std::pair<WeightType, Node<DataType>*>,
      std::vector<std::pair<WeightType, Node<DataType>*>>,
      std::greater<std::pair<WeightType, Node<DataType>*>>> minHeap;
    // acumulated distance from starting node to each node
    std::vector<std::pair<WeightType, size_t>>
      distances(nodeIndexes.size(), {defaultNoEdge<WeightType>()
        , nodeIndexes[startingNode]});
    // store temporal distance calculation
    WeightType newDistance = WeightType();

    // insert starting node with ititial distance
    minHeap.push(std::pair<WeightType, Node<DataType>*>
        (newDistance, startingNode));
    // set edge as true in validEdges
    validEdges[nodeIndexes[startingNode]][nodeIndexes[startingNode]] = true;
    // visit all unvisited adjacents

    while (!minHeap.empty()) {
      // get the node with the minimum distance
      std::pair<WeightType, Node<DataType>*> currentNode = minHeap.top();
      minHeap.pop();

      // traverse adjacent nodes comparing distances
      for (auto& adjacent : adjacencyList.at(currentNode.second)) {
        ++iterations;  // for each adyacent from actual node
        // only visit discovered nodes
        if ((discoveredElements.find(adjacent.first->getData())
            != discoveredElements.end())) {
          // calculate new distance = current distance + edge weight
          newDistance = currentNode.first + adjacent.second;
          // if the new distance is less than the saved distance
          if (newDistance < distances[nodeIndexes[adjacent.first]].first) {
            // set past measured edge as false
            this->updateEdgeIndex(validEdges, distances
              , nodeIndexes[adjacent.first], false);
            // update the distance for the adjacent node
            distances[nodeIndexes[adjacent.first]] = std::pair<WeightType, size_t>
              (newDistance, nodeIndexes[currentNode.second]);
            // mark the edge as measured
            this->updateEdgeIndex(validEdges, distances
              , nodeIndexes[adjacent.first], true);
            // push the adjacent node with its new distance into the minHeap
            minHeap.push(std::pair<WeightType, Node<DataType>*>
                (newDistance, adjacent.first));
          }
        }
      }
    }
    return iterations;
  }
};
