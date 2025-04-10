// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "Algorithm.hpp"

class BinarySearchTree {
 public:
  /**
   * @brief Standard node for a BST
   * 
   */
  struct Node {
    int64_t value = 0;
    Node* parent = nullptr;
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    ~Node();
  };

  // Constructor
  BinarySearchTree();
  // Disable copy and move
  BinarySearchTree(const BinarySearchTree& other) = delete;
  BinarySearchTree(BinarySearchTree&& other) = delete;
  BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
  BinarySearchTree& operator=(BinarySearchTree&& other) = delete;
  virtual ~BinarySearchTree();

  /**
   * @brief BST insertion
   * 
   * @param element key
   * @param iterations cost
   * @return Pointer to the inserted node
   */
  Node* insert(int64_t element, size_t& iterations);

  /**
   * @brief BST search
   * 
   * @param element key
   * @param iterations cost
   * @return Pointer to the target node or nullptr
   */
  virtual Node* search(int64_t element, size_t& iterations);

  /**
   * @brief BST deletion, unused
   * 
   * @param element key
   * @param iterations cost
   */
  /// void remove(int64_t element, size_t& iterations);

 protected:
  /**
   @brief method assigned to rotate a group of nodes to the left
   @param node node assigned to be rotated
   */
  void leftRotate(Node* node);

  /**
   @brief method assigned to rotate a group of nodes to the right
   @param node node assigned to be rotated
   */
  void rightRotate(Node* node);

 protected:
  Node* root = nullptr;
};
