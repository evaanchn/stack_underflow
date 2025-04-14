// Copyright 2025 stack_underflow CC-BY 4.0

#include "BTree.hpp"

BTreeNode::BTreeNode(bool leaf, int64_t t) {
  isLeaf = leaf;
  keyCount = 0;
  keys = std::vector<int64_t>(2 * t - 1, 0);
  children = std::vector<BTreeNode*>(2 * t, nullptr);
}

BTreeNode::~BTreeNode() {
}

bTree::bTree(int64_t t) : algorithm() {
  this->t = t;
  root = new BTreeNode(true, t);
  elementRecord.clear();
  algorithmName = "BTree";
}

bTree::~bTree() {
  clearTree(root);
  elementRecord.clear();
}

void bTree::clearTree(BTreeNode* node) {
  if (node == nullptr) return;
  
  if (!node->isLeaf) {
    for (int i = 0; i <= node->keyCount; i++) {
      clearTree(node->children[i]);
    }
  }
  delete node;
}

size_t bTree::insert(int64_t element) {
  if (elementRecord.find(element) != elementRecord.end()) {
    return 0;
  }
  size_t k = 0;
  BTreeNode* rootNode = root;

  if (rootNode->keyCount == (2 * t) - 1) {
    BTreeNode* newRoot = new BTreeNode(false, t);
    newRoot->children[0] = rootNode;
    root = newRoot;

    k += splitChild(newRoot, 0);
    k += insertNonFull(newRoot, element);
  } else {
    k += insertNonFull(rootNode, element);
  }

  elementRecord.insert(element);
  return k + 1;
}

size_t bTree::splitChild(BTreeNode* parentNode, int64_t i) {
  size_t k = 0;
  BTreeNode* fullChild = parentNode->children[i];
  BTreeNode* newChild = new BTreeNode(fullChild->isLeaf, t);

  // Copy right half of keys
  for (int j = 0; j < t - 1; j++) {
    newChild->keys[j] = fullChild->keys[j + t];
    k++;
  }
  newChild->keyCount = t - 1;

  // Copy children if not leaf
  if (!fullChild->isLeaf) {
    for (int j = 0; j < t; j++) {
      newChild->children[j] = fullChild->children[j + t];
      k++;
    }
  }

  // Move median key to parent
  for (int j = parentNode->keyCount; j > i; j--) {
    parentNode->keys[j] = parentNode->keys[j - 1];
  }
  parentNode->keys[i] = fullChild->keys[t - 1];
  parentNode->keyCount++;

  // Adjust parent's children
  for (int j = parentNode->keyCount; j > i + 1; j--) {
    parentNode->children[j] = parentNode->children[j - 1];
  }
  parentNode->children[i + 1] = newChild;

  // Update split node
  fullChild->keyCount = t - 1;
  return k;
}

size_t bTree::insertNonFull(BTreeNode* node, int64_t element) {
  size_t k = 0;
  int i = node->keyCount - 1;

  if (node->isLeaf) {
    while (i >= 0 && element < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      i--;
      k++;
    }
    node->keys[i + 1] = element;
    node->keyCount++;
  } else {
    while (i >= 0 && element < node->keys[i]) {
      i--;
      k++;
    }
    i++;

    if (node->children[i]->keyCount == (2 * t) - 1) {
      k += splitChild(node, i);
      if (element > node->keys[i]) {
        i++;
      }
    }
    k += insertNonFull(node->children[i], element);
  }
  return k;
}

size_t bTree::search(int64_t element) {
  size_t k = 0;
  BTreeNode* current = root;

  while (current != nullptr) {
    int i = 0;
    while (i < current->keyCount && element > current->keys[i]) {
      i++;
      k++;
    }

    if (i < current->keyCount && current->keys[i] == element) {
      return k + 1;
    }

    if (current->isLeaf) {
      return k;
    }

    current = current->children[i];
    k++;
  }

  return k;
}

size_t bTree::remove(int64_t element) {
  if (elementRecord.find(element) == elementRecord.end()) {
    return 0;
  }
  elementRecord.erase(element);
  return removeNavigation(root, element);
}

size_t bTree::removeNavigation(BTreeNode* node, int64_t element) {
  size_t k = 0;
  int i = 0;

  while (i < node->keyCount && element > node->keys[i]) {
    i++;
    k++;
  }

  if (i < node->keyCount && node->keys[i] == element) {
    if (node->isLeaf) {
      for (int j = i; j < node->keyCount - 1; j++) {
        node->keys[j] = node->keys[j + 1];
        k++;
      }
      node->keyCount--;
    } else {
      k += deleteInternalNode(node, element, i);
    }
    return k;
  }

  if (node->isLeaf) {
    return k;
  }

  return k + removeNavigation(node->children[i], element);
}

size_t bTree::deleteInternalNode(BTreeNode* node, int64_t element, int64_t i) {
  size_t k = 0;

  if (node->children[i]->keyCount >= t) {
    node->keys[i] = deletePredecessor(node->children[i], &k);
  } else if (node->children[i + 1]->keyCount >= t) {
    node->keys[i] = deleteSuccessor(node->children[i + 1], &k);
  } else {
    k += deleteMerge(node, i);
    k += removeNavigation(node->children[i], element);
  }

  return k;
}

int64_t bTree::deletePredecessor(BTreeNode* node, size_t* k) {
  if (node->isLeaf) {
    int64_t pred = node->keys[node->keyCount - 1];
    node->keyCount--;
    (*k)++;
    return pred;
  }

  (*k)++;
  return deletePredecessor(node->children[node->keyCount], k);
}

int64_t bTree::deleteSuccessor(BTreeNode* node, size_t* k) {
  if (node->isLeaf) {
    int64_t succ = node->keys[0];
    for (int i = 0; i < node->keyCount - 1; i++) {
      node->keys[i] = node->keys[i + 1];
      (*k)++;
    }
    node->keyCount--;
    return succ;
  }

  (*k)++;
  return deleteSuccessor(node->children[0], k);
}

size_t bTree::deleteMerge(BTreeNode* node, int64_t i) {
  size_t k = 0;
  BTreeNode* child = node->children[i];
  BTreeNode* sibling = node->children[i + 1];

  // Merge node key and sibling into child
  child->keys[child->keyCount] = node->keys[i];
  child->keyCount++;
  k++;

  // Copy sibling keys
  for (int j = 0; j < sibling->keyCount; j++) {
    child->keys[child->keyCount + j] = sibling->keys[j];
    k++;
  }

  // Copy children if not leaf
  if (!child->isLeaf) {
    for (int j = 0; j <= sibling->keyCount; j++) {
      child->children[child->keyCount + j] = sibling->children[j];
      k++;
    }
  }

  child->keyCount += sibling->keyCount;

  // Remove merged key from parent
  for (int j = i; j < node->keyCount - 1; j++) {
    node->keys[j] = node->keys[j + 1];
    k++;
  }

  // Remove sibling pointer
  for (int j = i + 1; j < node->keyCount; j++) {
    node->children[j] = node->children[j + 1];
    k++;
  }

  node->keyCount--;
  delete sibling;
  return k;
}
