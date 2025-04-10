// Copyright 2025 stack_underflow CC-BY 4.0

// sources:
// - https://www.w3schools.com/dsa/dsa_data_binarysearchtrees.php

#include <cassert>

#include "BinarySearchTree.hpp"


BinarySearchTree::BinarySearchTree() = default;

BinarySearchTree::Node::~Node() {
  delete this->leftChild;
  leftChild = nullptr;
  delete rightChild;
  rightChild = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
  if (this->root) {
    delete this->root;
    this->root = nullptr;
  }
}

BinarySearchTree::Node* BinarySearchTree::insert(int64_t element
    , size_t& iterations) {
  // create root node
  if (this->root == nullptr) {
    ++iterations;
    this->root = new Node();
    this->root->value = element;
    return this->root;
  }
  Node* node = this->root;
  while (node != nullptr) {
    ++iterations;
    // go left
    if (element < node->value) {
      // empty left
      if (node->leftChild == nullptr) {
        node->leftChild = new Node();
        node->leftChild->value = element;
        node->leftChild->parent = node;
        return node->leftChild;
      }
      node = node->leftChild;
    } else {  // go right: >=
      // empty right
      if (node->rightChild == nullptr) {
        node->rightChild = new Node();
        node->rightChild->value = element;
        node->rightChild->parent = node;
        return node->rightChild;
      }
      node = node->rightChild;
    }
  }
  return node;
}

BinarySearchTree::Node* BinarySearchTree::search(int64_t element
    , size_t& iterations) {
  if (this->root == nullptr) {
    // ++iterations;
    return nullptr;
  }
  Node* node = this->root;
  while (node != nullptr) {
    ++iterations;
    if (element == node->value) {
      break;
    } else if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
  }
  return node;
}

void BinarySearchTree::leftRotate(Node* node) {
  assert(node);
  Node* rightChild = node->rightChild;
  node->rightChild = rightChild->leftChild;
  if (rightChild->leftChild != nullptr) {
    rightChild->leftChild->parent = node;
  }
  rightChild->parent = node->parent;
  if (node->parent == nullptr) {
    this->root = rightChild;
  } else if (node == node->parent->leftChild) {
    node->parent->leftChild = rightChild;
  } else {
    node->parent->rightChild = rightChild;
  }
  rightChild->leftChild = node;
  node->parent = rightChild;
}

void BinarySearchTree::rightRotate(Node* node) {
  assert(node);
  Node* leftChild = node->leftChild;
  node->leftChild = leftChild->rightChild;
  if (leftChild->rightChild != nullptr) {
    leftChild->rightChild->parent = node;
  }
  leftChild->parent = node->parent;
  if (node->parent == nullptr) {
    root = leftChild;
  } else if (node == node->parent->rightChild) {
    node->parent->rightChild = leftChild;
  } else {
    node->parent->leftChild = leftChild;
  }
  leftChild->rightChild = node;
  node->parent = leftChild;
}
