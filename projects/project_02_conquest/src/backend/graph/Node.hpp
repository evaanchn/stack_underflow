// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <stdlib.h>
#include <string>

template <typename DataType>
class Node {
 private:
  DataType data;
  size_t id;

 public:
  /// @brief Default constructor
  Node() = default;

  /// @brief Constructure with direct data initialization.
  /// @param data Data to be stored.
  explicit Node(DataType data) : data(data) {}

  /// @brief Getter method.
  /// @return Data stored in node.
  DataType getData() { return this->data; }

  /// @brief Setter method
  /// @param data Data to be set.
  void setData(DataType data) { this->data = data; }
};

// Custom hash specialization for Node* so it works in unordered_map
template <typename DataType>
struct NodePtrHash {
  std::size_t operator()(const Node<DataType>* node) const {
    return std::hash<DataType>()(node->getData());
  }
};
