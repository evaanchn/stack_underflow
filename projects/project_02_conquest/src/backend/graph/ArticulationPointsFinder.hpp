// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <limits>

#include "Graph.hpp"

/// @brief Performs Tarjan's algorithm with recursion
/// @tparam DataType Data type of graph
/// @tparam WeightType Weight type of graph
template <typename DataType, typename WeightType>
class ArticulationPointsFinder {
 public:
  ArticulationPointsFinder() = default;

  // Main public method to find articulation points in a graph
  void findArticulationPoints(
      Graph<DataType, WeightType>* graph,
      std::unordered_set<Node<DataType>*>& articulationPoints) {
    // Adjacency list of the graph
    std::unordered_map<Node<DataType>*, std::unordered_map<Node<DataType>*
        , WeightType>>& adjList = graph->getAdjacencyList();

    // Visited flag for each node
    std::unordered_map<Node<DataType>*, bool> visited;

    // Discovery time of each node
    std::unordered_map<Node<DataType>*, int> discoveryTime;

    // Keeps track of low value for each node
    std::unordered_map<Node<DataType>*, int> low;

    // Parent pointer for DFS tree
    std::unordered_map<Node<DataType>*, Node<DataType>*> parent;

    int time = 0;  // Global time counter for discovery timestamps

    // Run DFS on each unvisited node (to handle disconnected graphs)
    for (const auto& pair : adjList) {
      Node<DataType>* node = pair.first;
      if (!visited[node]) {
        dfs(node, visited, discoveryTime, low, parent, articulationPoints
            , adjList, time);
      }
    }
  }

 private:
  // Recursive DFS function to find articulation points
  void dfs(Node<DataType>* actual,
      std::unordered_map<Node<DataType>*, bool>& visited,
      std::unordered_map<Node<DataType>*, int>& discoveryTime,
      std::unordered_map<Node<DataType>*, int>& low,
      std::unordered_map<Node<DataType>*, Node<DataType>*>& parent,
      std::unordered_set<Node<DataType>*>& articulationPoints,
      const std::unordered_map<Node<DataType>*
          , std::unordered_map<Node<DataType>*, WeightType>>& adjList,
      int& time) {
    // Mark the atual node as visited
    visited[actual] = true;
    // Set discovery and low to current time
    discoveryTime[actual] = low[actual] = ++time;
    int children = 0;  // Count of children in DFS tree

    // Iterate through all neighbors of actual node
    for (const auto& neighborPair : adjList.at(actual)) {
      Node<DataType>* neighbor = neighborPair.first;

      if (!visited[neighbor]) {
        // Tree Edge: neighbor is not visited and thus a child of actual node
        ++children;
        parent[neighbor] = actual;  // Set parent of neighbor to actual node

        // Recursively visit the child
        dfs(neighbor, visited, discoveryTime, low, parent, articulationPoints
            , adjList, time);

        // After visiting neighbor/child
        // , update `low[actual]` considering the lowest value reachable from
        // neighbor
        low[actual] = std::min(low[actual], low[neighbor]);

        // --- Articulation Point Conditions ---
        // Case 1: Actual node is root of DFS tree and has 2 or more children
        if (!parent[actual] && children > 1) {
          articulationPoints.insert(actual);
        }

        // Case 2: actual node is not root and `low[neighbor]`
        // is not able to reach above actual node
        if (parent[actual] && low[neighbor] >= discoveryTime[actual]) {
          articulationPoints.insert(actual);
        }
      } else if (neighbor != parent[actual]) {
        // Back Edge: neighbor is already visited and is not the parent
        // of actual node
        // This edge connects to an ancestor, so update `low[actual]`, in case
        // it is lower (following low's formula)
        low[actual] = std::min(low[actual], discoveryTime[neighbor]);
      }
    }
  }
};
