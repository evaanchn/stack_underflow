// Copyright 2025 stack_underflow CC-BY 4.0

// sources:
// - https://www.w3schools.com/dsa/dsa_data_binarysearchtrees.php

#include <cassert>

#include "BinarySearchTree.hpp"


BinarySearchTree::BinarySearchTree() = default;

BinarySearchTree::~BinarySearchTree() {
  this->clear();
}

void BinarySearchTree::clear() {
  if (this->root == nullptr) return;
  std::stack<Node*> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    Node* current = nodes.top();
    nodes.pop();

    if (current->leftChild) {
      nodes.push(current->leftChild);
    }
    if (current->rightChild) {
      nodes.push(current->rightChild);
    }
    delete current;
  }
  root = nullptr;
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
  assert(node->parent);  // not to be called by root
  Node *parent = node->parent;
  Node *oldLeft = node->leftChild;
  node->parent = NULL;
  // parent down left
  node->leftChild = parent;
  parent->parent = node;
  // old node->left as new node->left->right (parent left)
  parent->rightChild = oldLeft;
  if (oldLeft != NULL) oldLeft->parent = parent;
}

void BinarySearchTree::rightRotate(Node* node) {
  assert(node);
  assert(node->parent);  // not to be called by root
  Node *parent = node->parent;
  Node *oldRight = node->rightChild;
  node->parent = NULL;
  // parent down right
  node->rightChild = parent;
  parent->parent = node;
  // old node->right as newRight(parent) left
  parent->leftChild = oldRight;
  if (oldRight != NULL) oldRight->parent = parent;
}
