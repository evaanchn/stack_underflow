// Copyright 2025 stack_underflow CC-BY 4.0

#include <cassert>
#include <iostream>

#include "SplayTree.hpp"

SplayTree::SplayTree() : algorithm()
, BinarySearchTree() {
  algorithmName = "Splay Tree";
}

SplayTree::~SplayTree() {
  BinarySearchTree::~BinarySearchTree();
}

void SplayTree::toRoot(Node* node, size_t& iterations) {
  assert(node);
  if (node == this->root)  {
    this->root->parent = nullptr;
    return;
  }
  if (node->parent == nullptr) {
    std::cerr << "toRoot: lost node: " << node->value << std::endl;
    return;
  }
  Node* parent = node->parent;
  Node* grandParent = nullptr;
  while (node->parent->parent != nullptr) {
    ++iterations;
    parent = node->parent;
    grandParent = parent->parent;
    if (node == parent->leftChild) {
      if (parent == grandParent->leftChild) {
        zigZig(node);  // left -> left
      } else {
        zigZag(node);  // left -> right
      }
    } else {
      if (parent == grandParent->leftChild) {
        zagZig(node);  // right -> left
      } else {
        zagZag(node);  // right -> right
      }
    }
    // case that the trinode rotation ended in the root
    if (node->parent == nullptr) {
      this->root = node;
      this->root->parent = nullptr;
      return;
    }
  }
  // zig or zag
  if (node == node->parent->leftChild) {
    this->rightRotate(node->parent);
  } else {
    this->leftRotate(node->parent);
  }
  this->root = node;
  this->root->parent = nullptr;
  ++iterations;  // for the left or right rotation
}

size_t SplayTree::insert(int64_t element) {
  size_t iterations = 0;
  // bst insertion
  Node* inserted =  this->BinarySearchTree::insert(element, iterations);
  if (inserted == nullptr) {
    std::cerr << "SplayTree: failled to allocate node\n";
    return iterations;
  }
  this->elementRecord.insert(element);
  // move up
  this->toRoot(inserted, iterations);
  return iterations;
}

size_t SplayTree::search(int64_t element) {
  size_t iterations = 0;
  // search
  Node* node = this->search(element, iterations);
  // move up
  this->toRoot(node, iterations);
  return iterations;
}

BinarySearchTree::Node* SplayTree::search(int64_t element, size_t& iterations) {
  if (this->root == nullptr) {
    return nullptr;
  }
  Node* node = this->root;
  while (node != nullptr) {
    ++iterations;
    if (element == node->value) {
      // found
      break;
    } else if (element < node->value) {
      if (node->leftChild == nullptr) {
        // closest element found
        break;
      }
      node = node->leftChild;
    } else {
      if (node->rightChild == nullptr) {
        // closest element found
        break;
      }
      node = node->rightChild;
    }
  }
  return node;
}

size_t SplayTree::remove(int64_t element) {
  size_t iterations = 0;
  if (elementRecord.find(element) == elementRecord.end()
      || this->root == nullptr) {
    return iterations;
  }
  // search
  Node* removeNode =  this->search(element, iterations);
  if (removeNode->value == element) {
    // move up
    this->toRoot(removeNode, iterations);
    // remove
    removeRoot(iterations);
  }
  return iterations;
}

void SplayTree::removeRoot(size_t& iterations) {
  if (this->root == nullptr) return;
  Node* deleteNode = this->root;
  Node* leftChild = this->root->leftChild;
  Node* rightChild = this->root->rightChild;

  if (leftChild == nullptr) {
    this->root = rightChild;
  } else if (rightChild == nullptr) {
    this->root = leftChild;
  } else {
    this->root = maxNode(leftChild, iterations);
    if (this->root != leftChild) {
      this->root->parent->rightChild = this->root->leftChild;
      this->root->leftChild->parent = this->root->parent;
      this->root->leftChild = leftChild;
    }
    this->root->rightChild = rightChild;
  }
  // in case that deleteNode was the last one
  if (this->root != nullptr) this->root->parent = nullptr;
  deleteNode->leftChild = deleteNode->rightChild = nullptr;
  delete deleteNode;
  ++iterations;
}

BinarySearchTree::Node* SplayTree::maxNode(Node* parent, size_t& iterations) {
  assert(parent);
  while (parent->rightChild != nullptr) {
    ++iterations;
    parent = parent->rightChild;
  }
  return parent;
}

void SplayTree::zigZig(Node* node) {
  assert(node);
  Node* nodeChild = node->parent;
  Node* nodeGrandChild = node->parent->parent;
  // connect subtrees
  nodeGrandChild->leftChild = nodeChild->rightChild;
  nodeChild->leftChild = node->rightChild;
  // turn into zag zag
  node->parent = nodeGrandChild->parent;
  node->rightChild = nodeChild;
  nodeChild->parent = node;
  nodeChild->rightChild = nodeGrandChild;
  nodeGrandChild->parent = nodeChild;
}

void SplayTree::zigZag(Node* node) {
  assert(node);
  Node* leftChild = node->parent->parent;
  Node* rightChild = node->parent;
  // connect subtrees
  leftChild->rightChild = node->leftChild;
  rightChild->leftChild = node->rightChild;
  // node as parent
  node->parent = leftChild->parent;
  node->leftChild = leftChild;
  leftChild->parent = node;
  node->rightChild = rightChild;
  rightChild->parent = node;
}

void SplayTree::zagZag(Node* node) {
  assert(node);
  Node* nodeChild = node->parent;
  Node* nodeGrandChild = node->parent->parent;
  // connect subtrees
  nodeGrandChild->rightChild = nodeChild->leftChild;
  nodeChild->rightChild = node->leftChild;
  // turn into zig zig
  node->parent = nodeGrandChild->parent;
  node->leftChild = nodeChild;
  nodeChild->parent = node;
  nodeChild->leftChild = nodeGrandChild;
  nodeGrandChild->parent = nodeChild;
}

void SplayTree::zagZig(Node* node) {
  assert(node);
  Node* leftChild = node->parent;
  Node* rightChild = node->parent->parent;
  // connect subtrees
  leftChild->rightChild = node->leftChild;
  rightChild->leftChild = node->rightChild;
  // node as parent
  node->parent = rightChild->parent;
  node->leftChild = leftChild;
  leftChild->parent = node;
  node->rightChild = rightChild;
  rightChild->parent = node;
}
