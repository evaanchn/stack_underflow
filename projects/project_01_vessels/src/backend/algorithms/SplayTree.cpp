// Copyright 2025 stack_underflow CC-BY 4.0

#include <cassert>
#include <iostream>

#include "SplayTree.hpp"

SplayTree::SplayTree() : Algorithm()
, BinarySearchTree() {
  algorithmName = "Splay Tree";
}

SplayTree::~SplayTree() {
  BinarySearchTree::~BinarySearchTree();
}

void SplayTree::toRoot(Node* node, size_t& iterations) {
  assert(node);
  if (node == this->root)  {
    this->root->parent = nullptr;  // ensure not pointing to deleted
    return;
  }
  if (node->parent == nullptr) {
    return;
  }
  
  while (node->parent != nullptr) {
    ++iterations;
    Node* parent = node->parent;
    Node* grandParent = parent->parent;
    if (node == parent->leftChild) {  // left
      if (grandParent == nullptr) {
        this->rightRotate(node);
      } else if (parent == grandParent->leftChild) {
        zigZig(node);  // left -> left
      } else {
        zigZag(node);  // left -> right
      }
    } else {  // right
      if (grandParent == nullptr) {  
        this->leftRotate(node);
      } else if (parent == grandParent->leftChild) {
        zagZig(node);  // right -> left
      } else {
        zagZag(node);  // right -> right
      }
    }
  }
  this->root = node;
  this->root->parent = nullptr;
}

size_t SplayTree::insert(int64_t element) {
  size_t iterations = 0;
  // bst insertion
  Node* inserted =  this->BinarySearchTree::insert(element, iterations);
  if (inserted == nullptr) {
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
  if (removeNode == nullptr) return iterations;
  if (removeNode->value == element) {
    // move up
    this->toRoot(removeNode, iterations);
    // remove
    removeRoot(iterations);
    this->elementRecord.erase(element);
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
    // move up maxLeft
    Node* newRoot = maxNode(leftChild, iterations);
    this->root = leftChild;
    toRoot(newRoot, iterations);
    // reconect right subtree
    rightChild->parent = newRoot;
    newRoot->rightChild = rightChild;
  }
  this->root->parent = nullptr;
  deleteNode->leftChild = deleteNode->rightChild = nullptr;
  delete deleteNode;
  ++iterations;  // one for the remove process + toRoot cycles
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
  if (nodeGrandChild->leftChild !=  nullptr) {
    nodeGrandChild->leftChild->parent = nodeGrandChild;
  }
  nodeChild->leftChild = node->rightChild;
  if (nodeChild->leftChild !=  nullptr) {
    nodeChild->leftChild->parent = nodeChild;
  }
  // turn into zag zag (reconect the 3 nodes evaluated)
  
  node->parent = nodeGrandChild->parent;
  if (node->parent != nullptr) {
    if (this->root == nodeGrandChild) {
    }
    if (node->parent->leftChild == nodeGrandChild) {
      node->parent->leftChild = node;
    } else {
      node->parent->rightChild = node;
    }
  }
  // node as parent
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
  if (leftChild->rightChild != nullptr) {
    leftChild->rightChild->parent = leftChild;
  }
  rightChild->leftChild = node->rightChild;
  if (rightChild->leftChild != nullptr) {
    rightChild->leftChild->parent = rightChild;
  }
  // inherit grandParent parent
  node->parent = leftChild->parent;
  if (node->parent != nullptr) {
    if (this->root == leftChild) {
    }
    if (node->parent->leftChild == leftChild) {
      node->parent->leftChild = node;
    } else {
      node->parent->rightChild = node;
    }
  }
  // node as parent
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
  if (nodeGrandChild->rightChild !=  nullptr) {
    nodeGrandChild->rightChild->parent = nodeGrandChild;
  }
  nodeChild->rightChild = node->leftChild;
  if (nodeChild->rightChild !=  nullptr) {
    nodeChild->rightChild->parent = nodeChild->rightChild;
  }
  // turn into zig zig
  // inherit grandParent parent
  node->parent = nodeGrandChild->parent;
  if (node->parent != nullptr) {
    if (node->parent->leftChild == nodeGrandChild) {
      node->parent->leftChild = node;
    } else {
      node->parent->rightChild = node;
    }
  }
  // node as parent
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
  if (leftChild->rightChild != nullptr) {
    leftChild->rightChild->parent = leftChild;
  }
  rightChild->leftChild = node->rightChild;
  if (rightChild->leftChild != nullptr) {
    rightChild->leftChild->parent = rightChild;
  }
  // inherit grandParent parent
  node->parent = rightChild->parent;
  if (node->parent != nullptr) {
    if (node->parent->leftChild == rightChild) {
      node->parent->leftChild = node;
    } else {
      node->parent->rightChild = node;
    }
  }
  // node as parent
  node->leftChild = leftChild;
  leftChild->parent = node;
  node->rightChild = rightChild;
  rightChild->parent = node;
}

// In-order traversal function for debug
void SplayTree::inorderTraversal(Node* root) {
  if (root == nullptr)
    return;
  inorderTraversal(root->leftChild);
  std::cout << root->value << " ";
  inorderTraversal(root->rightChild);
}
