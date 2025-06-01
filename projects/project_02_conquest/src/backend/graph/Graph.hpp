// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <limits>
#include <vector>
#include <unordered_map>

#include "Node.hpp"

#define DIRECTED true

/**
 * @brief Returns a default value indicating no edge between two nodes.
 * 
 * If the type is floating-point, it returns positive infinity.
 * Otherwise, it returns a large number (1e9) casted to the type.
 *
 * @tparam DataType The data type used for edge weights.
 * @return DataType The default "no edge" value.
 */
template <typename DataType>
DataType defaultNoEdge() {
  if constexpr (std::is_floating_point<DataType>::value)
    return std::numeric_limits<DataType>::infinity();
  else
    return static_cast<DataType>(1e9);
}

/**
 * @brief A generic graph data structure supporting both adjacency matrix and 
 * list representations.
 *
 * @tparam DataType The type stored in the nodes.
 * @tparam WeightType The type used for edge weights.
 */
template <typename DataType, typename WeightType>
class Graph {
 private:
  /// Whether the graph is directed.
  bool directed = !DIRECTED;

  /// The sentinel value used to represent no edge between nodes.
  WeightType noEdge = defaultNoEdge<WeightType>();

  /// Adjacency matrix representation of the graph.
  std::vector<std::vector<WeightType>> adjacencyMatrix;

  /// Adjacency list representation of the graph.
  std::unordered_map<Node<DataType>*, std::unordered_map<Node<DataType>*
      , WeightType>> adjacencyList;

  /// List of all nodes in the graph.
  std::vector<Node<DataType>*> nodes;

  /// Maps nodes to their corresponding index in the adjacency matrix.
  std::unordered_map<Node<DataType>*, size_t> nodeIndexes;

 public:
  /**
   * @brief Constructs a new Graph.
   * 
   * @param isDirected Whether the graph is directed (default: !DIRECTED macro).
   * @param isWeighed Whether the graph uses weights (default: !WEIGHED macro).
   */
  explicit Graph(bool isDirected = !DIRECTED) : directed(isDirected) {}

  /**
   * @brief Destructor: deletes all dynamically allocated nodes.
   */
  ~Graph() {
    for (auto* node : this->nodes) {
      if (node) delete node;
    }
  }

 public:
  /// @brief Adds a node to the graph.
  /// @param node Pointer to node that will be added to the graph.
  void addNode(Node<DataType>* node) {
    // If node has not been added yet
    if (this->nodeIndexes.find(node) == this->nodeIndexes.end()) {
      // Add node to nodes vector and corresponding index too
      this->nodes.push_back(node);
      this->nodeIndexes[node] = this->nodes.size() - 1;
      // Add node to adjacencyList, with intialized map of node and weight
      this->adjacencyList[node] = std::unordered_map<Node<DataType>*
          , WeightType>();
      // Add an additional space for the new node for every node
      for (auto &nodeRow : this->adjacencyMatrix) {
        nodeRow.push_back(this->noEdge);
      }

      // Create new node row, with same amount of cols as existing nodes + 1
      std::vector<WeightType> newNodeRow = std::vector<WeightType>();
      for (size_t nodeRow = 0; nodeRow < this->adjacencyMatrix.size() + 1
          ; ++nodeRow) {
        newNodeRow.push_back(this->noEdge);
      }
      this->adjacencyMatrix.push_back(newNodeRow);
    }
  }

  /// @brief Adds an edge between two nodes.
  /// @param source The source node.
  /// @param destiny The destiny where an edge will connect.
  /// @param weight Weight added.
  void addEdge(Node<DataType>* source, Node<DataType>* destiny
      , WeightType weight) {
    // First add the source and destiny nodes, if not added already
    addNode(source);
    addNode(destiny);

    // Get indexes
    size_t sourceIndex = nodeIndexes[source];
    size_t destinyIndex = nodeIndexes[destiny];
    // Add an edge in adjacency matrix
    this->adjacencyMatrix[sourceIndex][destinyIndex] = weight;
    this->adjacencyList[source][destiny] = weight;

    // Add an edge back from destiny to source if the graph is not directed
    if (!directed) {
      this->adjacencyMatrix[destinyIndex][sourceIndex] = weight;
      this->adjacencyList[destiny][source] = weight;
    }
  }

  /// @brief Removes a node from the graph.
  /// @param node Node to be removed.
  void removeNode(Node<DataType>* node) {
    // Ensure removal of an existing node
    if (this->nodeIndexes.find(node) != nodeIndexes.end()) {
      // Find the iterator for the node in the node vector
      auto nodeIt = std::find(this->nodes.begin(), this->nodes.end(), node);
      // If node had connections
      if (this->adjacencyList.find(node) != this->adjacencyList.end()) {
        // Remove the edges to the node from it's neighbors in the list
        for (auto& pair : this->adjacencyList) {
          pair.second.erase(node);
        }
        // Remove the edges to the neighbors in the list
        this->adjacencyList.erase(node);
        size_t index = std::distance(this->nodes.begin(), nodeIt);

        // Erase the node's row in adjacency matrix
        this->adjacencyMatrix.erase(this->adjacencyMatrix.begin() + index);
        // Erase the column for the node in each node's row
        for (auto& row : this->adjacencyMatrix) {
          row.erase(row.begin() + index);
        }
      }

      // Erase node from node vector
      this->nodes.erase(nodeIt);
      // Erase node index from record of indexess
      this->nodeIndexes.erase(node);
      // Update the indexes in the index record
      for (size_t nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex) {
        // If node still exists
        if (this->nodeIndexes.find(this->nodes[nodeIndex])
            != this->nodeIndexes.end()) {
          // Update index
          this->nodeIndexes[this->nodes[nodeIndex]] = nodeIndex;
        }
      }

      delete node;
    }
  }

  /// @brief Removes an edge between to nodes.
  /// @param source Source node.
  /// @param destiny Destiny node.
  void removeEdge(Node<DataType>* source, Node<DataType>* destiny) {
    if (adjacencyList.find(source) != adjacencyList.end()
        && adjacencyList.find(destiny) != adjacencyList.end()) {
      // Get source and destiny's indexes
      size_t sourceIndex = nodeIndexes[source];
      size_t destinyIndex = nodeIndexes[destiny];
      // Reset in source, destiny to no edge
      this->adjacencyMatrix[sourceIndex][destinyIndex] = this->noEdge;
      // Remove the destiny from the source's list
      this->adjacencyList[source].erase(destiny);

      // If the graph is not directed, remove source from destiny too
      if (!directed) {
        this->adjacencyMatrix[destinyIndex][sourceIndex] = this->noEdge;
        this->adjacencyList[destiny].erase(source);
      }
    }
  }

 public:
  /// @brief Getter for adjacency matrix
  std::vector<std::vector<WeightType>>& getAdjacencyMatrix() {
    return this->adjacencyMatrix;
  }

  /// @brief Getter for adjacency list
  std::unordered_map<Node<DataType>*, std::unordered_map<Node<DataType>*
      , WeightType>>& getAdjacencyList() {
    return this->adjacencyList;
  }

  /// @brief Getter for nodes vector
  std::vector<Node<DataType>*>& getNodes() {
    return this->nodes;
  }
};
