// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <unordered_set>
#include "Algorithm.hpp"

#define MAX_KEYS 3
#define MIN_KEYS 1

class BTreeNode {
 public:
    int64_t keyCount;
    int64_t keys[MAX_KEYS];
    BTreeNode* children[MAX_KEYS + 1];
    bool isLeaf;

    /**
     @brief constructor method of the class
     @param leaf determines whether the BTreenode is a leaf
    */
    explicit BTreeNode(bool leaf);
};

class bTree : public algorithm {
 public:
    /**
     @brief constructor method of the class
     @param t minimum tree grade
    */
    explicit bTree(int64_t t);

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
    BTreeNode* root;
    int64_t t;

    /**
     @brief splits child nodes to create more nodes
     @param parentNode parent node whose children will be modified
     @param i index used to locate children
     @return the number of iterations made for the insertion process
    */
    size_t splitChild(BTreeNode* parentNode, int64_t i);

    /**
     @brief allows to Insert an element into a node that is not full
     @param node node that has to be evaluated
     @param element value assigned to the node
     @return the number of iterations made for the insertion process
    */
    size_t insertNonFull(BTreeNode* node, int64_t element);

    /**
     @brief Allows to navigate the tree to find a node
     @param interactions Counter assigned to save the number of sets performed
     @see insertNonFull
    */
    BTreeNode* searchNavigation(BTreeNode* temp, int64_t element,
      size_t* interactions);

    /**
     @brief Allows to navigate the tree to delete a node
     @see insertNonFull
    */
    size_t removeNavigation(BTreeNode* temp, int64_t element);

    /**
     @brief handles the deletion of a element within an internal node
     @see splitChild and insertNonFull
    */
    size_t deleteInternalNode(BTreeNode* node, int64_t element, int64_t i);

    /**
     @brief seeks to remove the largest element from the left subtree of a node
     @see search
    */
    int64_t deletePredecessor(BTreeNode* node, size_t* interactions);

    /**
     @brief seeks to remove the smallest key from the left subtree of a node
     @see search
    */
    int64_t deleteSuccessor(BTreeNode* node, size_t* interactions);

    /**
     @brief handles the merger of two child nodes
     @see deleteInternalNode
    */
    size_t deleteMerge(BTreeNode* node, int64_t i);
};
