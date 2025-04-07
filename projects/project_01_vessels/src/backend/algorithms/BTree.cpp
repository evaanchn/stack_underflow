// Copyright 2025 stack_underflow CC-BY 4.0

#include "BTree.hpp"

BTreeNode::BTreeNode(bool leaf) {
  isLeaf = leaf;
  keyCount = 0;
  for (int64_t i = 0; i < (MAX_KEYS + 1); ++i) {
    children[i] = nullptr;
  }
}

bTree::bTree(int64_t t) : algorithm() {
  this->t = t;
  root = new BTreeNode(true);
  algorithmName = "BTree";
}

size_t bTree::insert(int64_t element) {
  size_t interactions = 0;
  BTreeNode* rootNode = root;
  int64_t t = this->t;
  interactions += 2;  // save interactions

  if (rootNode->keyCount == (2 * t) - 1) {
    BTreeNode* newRoot = new BTreeNode(false);
    root = newRoot;
    newRoot->children[0] = rootNode;
    newRoot->keyCount = 1;
    interactions += 4;  // save interactions

    // save interactions
    interactions += splitChild(newRoot, 0);
    interactions += insertNonFull(newRoot, element);
  } else {
    // save interactions
    interactions += insertNonFull(rootNode, element);
  }
  return interactions;
}

size_t bTree::search(int64_t element) {
  size_t interactions = 0;
  BTreeNode* temp = nullptr;
  temp = searchNavigation(temp, element, &interactions);
  return interactions;
}

BTreeNode* bTree::searchNavigation(BTreeNode* temp, int64_t element,
  size_t* interactions) {
  if (temp == nullptr) {
    temp = root;
    ++(*interactions);  // save interactions
  }

  int i = 0;
  while (i < temp->keyCount && element > temp->keys[i]) {
    i++;
    ++(*interactions);  // save interactions
  }
  if (i < temp->keyCount && element == temp->keys[i]) {
    return temp;
  } else if (temp->isLeaf) {
    return nullptr;
  } else {
    return searchNavigation(temp->children[i], element, interactions);
  }
}

size_t bTree::remove(int64_t element) {
  return removeNavigation(root, element);
}

size_t bTree::removeNavigation(BTreeNode* temp, int64_t element) {
  size_t interactions = 0;
  int i = 0;
  ++interactions;  // save interactions

  while (i < temp->keyCount && element > temp->keys[i]) {
    ++i;
    ++interactions;  // save interactions
  }

  if (i < temp->keyCount && element == temp->keys[i]) {
    if (temp->isLeaf) {
      for (int j = i; j < temp->keyCount - 1; ++j) {
        temp->keys[j] = temp->keys[j + 1];
        ++interactions;  // save interactions
      }

      temp->keyCount--;
      ++interactions;  // save interactions

    } else {
      // save interactions
      interactions += deleteInternalNode(temp, element, i);
    }
  } else if (!temp->isLeaf) {
    // save interactions
    interactions += removeNavigation(temp->children[i], element);
  }
  return interactions;
}

size_t bTree::splitChild(BTreeNode* parentNode, int64_t i) {
  size_t interactions = 0;
  int64_t t = this->t;
  BTreeNode* fullChild = parentNode->children[i];
  BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);
  interactions += 3;  // save interactions

  for (int64_t j = parentNode->keyCount; j > i; --j) {
    parentNode->children[j + 1] = parentNode->children[j];
    parentNode->keys[j] = parentNode->keys[j - 1];
    interactions += 2;  // save interactions
  }

  parentNode->children[i + 1] = newChild;
  parentNode->keys[i] = fullChild->keys[t - 1];
  parentNode->keyCount++;
  interactions += 3;  // save interactions

  newChild->keyCount = t - 1;
  ++interactions;  // save interactions

  for (int64_t j = 0; j < t - 1; ++j) {
    newChild->keys[j] = fullChild->keys[t + j];
    ++interactions;  // save interactions
  }

  fullChild->keyCount = t - 1;
  ++interactions;  // save interactions

  if (!fullChild->isLeaf) {
    for (int64_t j = 0; j < t; ++j) {
      newChild->children[j] = fullChild->children[t + j];
      ++interactions;  // save interactions
    }
  }
  return interactions;
}

size_t bTree::insertNonFull(BTreeNode* node, int64_t element) {
  size_t interactions = 0;
  int64_t i = node->keyCount - 1;
  ++interactions;  // save interactions

  if (node->isLeaf) {
    while (i >= 0 && element < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      --i;
      interactions += 2;  // save interactions
    }

    node->keys[i + 1] = element;
    node->keyCount++;
    interactions += 2;  // save interactions

  } else {
    while (i >= 0 && element < node->keys[i]) {
      --i;
      ++interactions;  // save interactions
    }

    ++i;
    ++interactions;  // save interactions

    if (node->children[i]->keyCount == (2 * t) - 1) {
      splitChild(node, i);
      ++interactions;  // save interactions

      if (element > node->keys[i]) {
        ++i;
        ++interactions;  // save interactions
      }
    }
    // save interactions
    interactions += insertNonFull(node->children[i], element);
  }
  return interactions;
}

size_t bTree::deleteInternalNode(BTreeNode* node, int64_t element, int64_t i) {
  size_t interactions = 0;
  int64_t t = this->t;
  if (node->children[i]->keyCount >= t) {
    // save interactions
    node->keys[i] = deletePredecessor(node->children[i], &interactions);
  } else if (node->children[i + 1]->keyCount >= t) {
    // save interactions
    node->keys[i] = deleteSuccessor(node->children[i + 1], &interactions);
  } else {
    // save interactions
    interactions += deleteMerge(node, i);
    interactions += deleteInternalNode(node->children[i], element, t - 1);
  }
  return interactions;
}

int64_t bTree::deletePredecessor(BTreeNode* node, size_t* interactions) {
  while (!node->isLeaf) {
    node = node->children[node->keyCount - 1];
    ++(*interactions);  // save interactions
  }

  int64_t element = node->keys[node->keyCount - 1];
  node->keyCount--;
  (*interactions) += 2;  // save interactions

  return element;
}

int64_t bTree::deleteSuccessor(BTreeNode* node, size_t* interactions) {
  while (!node->isLeaf) {
    node = node->children[0];
    ++(*interactions);  // save interactions
  }

  int64_t element = node->keys[0];
  ++(*interactions);  // save interactions

  for (int64_t i = 0; i < node->keyCount - 1; ++i) {
    node->keys[i] = node->keys[i + 1];
    ++(*interactions);  // save interactions
  }

  node->keyCount--;
  ++(*interactions);  // save interactions
  return element;
}

size_t bTree::deleteMerge(BTreeNode* node, int64_t i) {
  size_t interactions = 0;
  BTreeNode* leftChild = node->children[i];
  BTreeNode* rightChild = node->children[i + 1];
  interactions += 2;  // save interactions

  leftChild->keys[leftChild->keyCount] = node->keys[i];
  leftChild->keyCount++;
  interactions += 2;  // save interactions

  for (int64_t j = 0; j < rightChild->keyCount; ++j) {
    leftChild->keys[leftChild->keyCount + j] = rightChild->keys[j];
    leftChild->keyCount++;
    interactions += 2;  // save interactions
  }

  if (!leftChild->isLeaf) {
    for (int64_t j = 0; j < rightChild->keyCount + 1; ++j) {
      leftChild->children[leftChild->keyCount + j] = rightChild->children[j];
      ++interactions;  // save interactions
    }
  }

  for (int64_t j = i; j < node->keyCount - 1; ++j) {
    node->keys[j] = node->keys[j + 1];
    node->children[j + 1] = node->children[j + 2];
    interactions += 2;  // save interactions
  }

  node->keyCount--;
  ++interactions;  // save interactions

  delete rightChild;
  return interactions;
}
