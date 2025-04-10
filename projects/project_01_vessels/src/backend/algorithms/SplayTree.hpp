// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "Algorithm.hpp"
#include "BinarySearchTree.hpp"

class SplayTree : public algorithm
, public BinarySearchTree {
 public:
  /// @brief constructor method of the class
  SplayTree();
  // Disable copy and move
  SplayTree(const SplayTree& other) = delete;
  SplayTree(SplayTree&& other) = delete;
  SplayTree& operator=(const SplayTree& other) = delete;
  SplayTree& operator=(SplayTree&& other) = delete;
  ~SplayTree();

  /**
   @brief assigned method for inserting elements
  @param element element to insert
  @return the number of iterations made for the insertion process
   */
  size_t insert(int64_t element) override;

  /**
   @brief method assigned to search for elements
  @see insert
   */
  size_t search(int64_t element) override;

  /**
   * @brief Splay search
   * 
   * @param element key
   * @param iterations cost
   * @return Pointer to the target or the closest node found
   */
  Node* search(int64_t element, size_t& iterations) override;

  /**
   @brief method assigned for removing elements
  @see insert
   */
  size_t remove(int64_t element) override;

 private:
  /**
   * @brief Move up a node into the root
   * 
   * @param node 
   */
  void toRoot(Node* node, size_t& iterations);

  /**
   * @brief Delete root and reconect subtrees
   * 
   * @param iterations 
   */
  void removeRoot(size_t& iterations);

  /**
   * @brief Obtain the max value node in a subtree
   * 
   * @param root subtree root
   * @param iterations 
   * @return Node* max
   */
  Node* maxNode(Node* root, size_t& iterations);
  /**
   * @brief node is left and node.parent is left
   * 
   * @param node 
   */
  void zigZig(Node* node);
  /**
   * @brief node is left and node.parent is right
   * 
   * @param node 
   */
  void zigZag(Node* node);
  /**
   * @brief node is right and node.parent is right
   * 
   * @param node 
   */
  void zagZag(Node* node);
  /**
   * @brief node is right and node.parent is left
   * 
   * @param node 
   */
  void zagZig(Node* node);
};
