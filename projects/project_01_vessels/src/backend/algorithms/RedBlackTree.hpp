// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include "Algorithm.hpp"

class RedBlackTree : public Algorithm {
 public:
  struct Node {
    int64_t value;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    std::string color;
  };

 public:
  /// @brief constructor method of the class
  RedBlackTree();

  /// @brief destructor method of the class
  ~RedBlackTree();

  /// @brief method that allows to eliminate every single node of the tree
  void clear();

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
   @brief method assigned for removing elements
   @see insert
   */
  size_t remove(int64_t element) override;

 protected:
  Node* root;
  Node* NIL;

  /**
   @brief method assigned to rotate a group of nodes to the left
   @param node node assigned to be rotated
   @return the number of iterations made for the insertion process
   */
  size_t leftRotate(Node* node);

  /**
   @brief method assigned to rotate a group of nodes to the right
   @see leftRotate
   */
  size_t rightRotate(Node* node);

  /**
   @brief method assigned to fix / equilibrate the tree after inserting a node
   @see leftRotate
   */
  size_t insertFixup(Node* node);

  /**
   @brief method assigned to fix / equilibrate the tree after deleting a node
   @see leftRotate
   */
  size_t deleteFixup(Node* node);

  /**
   @brief method assigned to transplate two nodes in the tree
   @see leftRotate
   */
  size_t transplant(Node* u, Node* v);

  /**
   @brief method assigned to obtain the node with the smallest value
   @param node node used to search the tree
   @param interactions number of interactions or steps performed in the method
   @return the smallest node obtained in the tree search
   */
  Node* minimum(Node* node, size_t* interactions);
};
