// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>
#include "Algorithm.hpp"

struct Node {
  size_t value;
  Node* leftChild;
  Node* rightChild;
  std::string color;
};

class redBlackTree : public algorithm {
 public:
    /// @brief constructor method of the class
    redBlackTree();
 private:
    Node root;
};
