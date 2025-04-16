// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_set>
#include "Algorithm.hpp"

/**
 * @class BTreeNode
 * @brief Node structure for B-Tree implementation
 */
class BTreeNode {
 public:
  std::vector<int64_t> keys;
  std::vector<BTreeNode*> children;
  bool isLeaf;
  int64_t keyCount;

  /**
   * @brief constructor method of the class
   * @param leaf Boolean indicating if the node is a leaf
   * @param t Minimum degree of the B-Tree
   */
  explicit BTreeNode(bool leaf, int64_t t);

  /// @brief Destructor method of the class
  ~BTreeNode();
};

/**
 * @class BTree
 * @brief B-Tree implementation that inherits from algorithm base class
 */
class BTree : public Algorithm {
 public:
  /**
   * @brief constructor method of the class
   * @param t Minimum degree of the B-Tree
   */
  explicit BTree(int64_t t);

  /// @brief Destructor method
  ~BTree();

  /**
   * @brief method that allows to eliminate every single node of the tree
   * @param node node that will be eliminated
   */
  void clearTree(BTreeNode* node);

  /**
   * @brief Inserts an element into the B-Tree
   * @param element Element to be inserted
   * @return Number of operations performed during insertion
   */
  size_t insert(int64_t element) override;

  /**
   * @brief Searches for an element in the B-Tree
   * @param element Element to search for
   * @return Number of operations performed during search
   */
  size_t search(int64_t element) override;

  /**
   * @brief Removes an element from the B-Tree
   * @param element Element to be removed
   * @return Number of operations performed during removal
   */
  size_t remove(int64_t element) override;

 protected:
  BTreeNode* root;
  int64_t t;
  std::unordered_set<int64_t> elementRecord;

  /**
   * @brief Splits a full child node
   * @param parentNode Parent of the node to be split
   * @param i Index of the child to be split
   * @return Number of operations performed
   */
  size_t splitChild(BTreeNode* parentNode, int64_t i);

  /**
   * @brief Inserts an element into a non-full node
   * @param node Node to insert into
   * @param element Element to be inserted
   * @return Number of operations performed
   */
  size_t insertNonFull(BTreeNode* node, int64_t element);

  /**
   * @brief Navigates through the tree to find a node
   * @param temp Current node being examined
   * @param element Element to search for
   * @param interactions Counter for operations performed
   * @return Node containing the element, or nullptr if not found
   */
  BTreeNode* searchNavigation(BTreeNode* temp, int64_t element,
    size_t* interactions);

  /**
   * @brief Navigates through the tree to remove an element
   * @param temp Current node being examined
   * @param element Element to be removed
   * @return Number of operations performed
   */
  size_t removeNavigation(BTreeNode* temp, int64_t element);

  /**
   * @brief Handles deletion of an element from an internal node
   * @param node Node containing the element
   * @param element Element to be deleted
   * @param i Index of the element
   * @return Number of operations performed
   */
  size_t deleteInternalNode(BTreeNode* node, int64_t element, int64_t i);

  /**
   * @brief Finds and removes the predecessor of a key
   * @param node Node to start searching from
   * @param interactions Counter for operations performed
   * @return The predecessor key value
   */
  int64_t deletePredecessor(BTreeNode* node, size_t* interactions);

  /**
   * @brief Finds and removes the successor of a key
   * @param node Node to start searching from
   * @param interactions Counter for operations performed
   * @return The successor key value
   */
  int64_t deleteSuccessor(BTreeNode* node, size_t* interactions);

  /**
   * @brief Merges two child nodes
   * @param node Parent node of the children to merge
   * @param i Index of the first child to merge
   * @return Number of operations performed
   */
  size_t deleteMerge(BTreeNode* node, int64_t i);
};
