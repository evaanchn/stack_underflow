// Copyright 2025 stack_underflow CC-BY 4.0

#include "BTree.hpp"

BTreeNode::BTreeNode(bool isLeaf) : leaf(isLeaf){}

BTreeNode::~BTreeNode() {
}

BTree::BTree(int64_t t) : Algorithm() {
  this->t = t;
  root = new BTreeNode(true);
  algorithmName = "BTree";
}

BTree::~BTree() {
  clearTree(root);
}

void BTree::clearTree(BTreeNode* node) {
  if (node == nullptr) return;

  if (!node->leaf) {
    for (size_t i = 0; i <= node->keys.size(); ++i) {
      clearTree(node->children[i]);
    }
  }
  delete node;
}

size_t BTree::insert(int64_t element) {
  elementRecord.insert(element);
  size_t k = 0;
  if (root->keys.size() == (2 * t - 1)) {
    BTreeNode* newRoot = new BTreeNode(false);
    newRoot->children.push_back(root);
    k += splitChild(newRoot, 0);
    root = newRoot;
    k += insertNonFull(root, element);
  } else {
    k += insertNonFull(root, element);
  }
  ++k;
  return k;
}

size_t BTree::borrowFromSibling(BTreeNode* node, int i, int siblingIndex) {
  size_t k = 0;
  BTreeNode* child = node->children[i];
  BTreeNode* sibling = node->children[siblingIndex];

  if (siblingIndex < i) {
    child->keys.insert(child->keys.begin(), node->keys[i - 1]);
    node->keys[i - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    k += 2;
    if (!sibling->leaf) {
      child->children.insert(child->children.begin(), 
        sibling->children.back());
      sibling->children.pop_back();
      k += 2;
    }
  } else {
    child->keys.push_back(node->keys[i]);
    node->keys[i] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    k += 2;
    if (!sibling->leaf) {
      child->children.push_back(sibling->children.front());
      sibling->children.erase(sibling->children.begin());
      k += 2;
    }
  }
  return k;
}

size_t BTree::splitChild(BTreeNode* parentNode, int64_t i) {
  BTreeNode* fullChild = parentNode->children[i];
  BTreeNode* newChild = new BTreeNode(fullChild->leaf);

  parentNode->children.insert(parentNode->children.begin() + i + 1, newChild);
  parentNode->keys.insert(parentNode->keys.begin() + i, fullChild->keys[t - 1]);

  newChild->keys.assign(fullChild->keys.begin() + t, fullChild->keys.end());
  fullChild->keys.resize(t - 1);

  if (!fullChild->leaf) {
    newChild->children.assign(fullChild->children.begin() + t, 
      fullChild->children.end());
    fullChild->children.resize(t);
  }
  return 1;
}

size_t BTree::insertNonFull(BTreeNode* node, int64_t element) {
  size_t k = 0;
  int64_t i = node->keys.size() - 1;

  if (node->leaf) {
    node->keys.push_back(0);
    while (i >= 0 && element < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      --i;
      ++k;
    }
    node->keys[i + 1] = element;
  } else {
    while (i >= 0 && element < node->keys[i]) {
      --i;
      ++k;
    }
    ++i;
    if (node->children[i]->keys.size() == (2 * t - 1)) {
      k += splitChild(node, i);
      if (element > node->keys[i]) {
        ++i;
      }
    }
    k += insertNonFull(node->children[i], element);
    ++k;
  }
  return k;
}

size_t BTree::search(int64_t element) {
  size_t k = 0;
  BTreeNode* current = root;

  while (current != nullptr) {
    size_t i = 0;
    while (i < current->keys.size() && element > current->keys[i]) {
      ++i;
      ++k;
    }

    if (i < current->keys.size() && current->keys[i] == element) {
      return k + 1;
    }

    if (current->leaf) {
      return k;
    }

    current = current->children[i];
    ++k;
  }
  return k;
}

size_t BTree::remove(int64_t element) {
  if (elementRecord.find(element) == elementRecord.end()) {
    return 0;
  }
  elementRecord.erase(element);
  size_t k = removeNavigation(root, element);

  if (!root->leaf && root->keys.empty()) {
    BTreeNode* oldRoot = root;
    root = root->children[0];
    delete oldRoot;
  }

  return k;
}

size_t BTree::removeNavigation(BTreeNode* node, int64_t element) {
  size_t k = 0;
  size_t i = 0;

  while (i < node->keys.size() && element > node->keys[i]) {
    ++i;
    ++k;
  }

  if (node->leaf) {
    if (i < node->keys.size() && node->keys[i] == element) {
      node->keys.erase(node->keys.begin() + i);
    }
    ++k;
    return k;
  }

  if (i < node->keys.size() && node->keys[i] == element) {
      k += deleteInternalNode(node, element, i);
  } else {
    if (node->children[i]->keys.size() < t) {
      if (i > 0 && node->children[i-1]->keys.size() >= t) {
        k += borrowFromSibling(node, i, i-1);
      } else if (i < node->children.size()-1 && node->children[i+1]->keys.size() >= t) {
        k += borrowFromSibling(node, i, i+1);
      } else {
        if (i < node->children.size()-1) {
          k += deleteMerge(node, i);
        } else {
          k += deleteMerge(node, i-1);
          i--;
        }
      }
    }
    k += removeNavigation(node->children[i], element);
  }
  return k;
}

size_t BTree::deleteInternalNode(BTreeNode* node, int64_t element, size_t i) {
  size_t k = 0;
  if (node->children[i]->keys.size() >= t) {
    node->keys[i] = deletePredecessor(node->children[i], &k);
  } else if (node->children[i + 1]->keys.size() >= t) {
    node->keys[i] = deleteSuccessor(node->children[i + 1], &k);
  } else {
    k += deleteMerge(node, i);
    k += removeNavigation(node->children[i], element);
  }
  return k;
}

int64_t BTree::deletePredecessor(BTreeNode* node, size_t* k) {
  while (!node->leaf) {
    node = node->children.back();
    ++(*k);
  }
  int64_t val = node->keys.back();
  node->keys.pop_back();
  ++(*k);
  return val;
}

int64_t BTree::deleteSuccessor(BTreeNode* node, size_t* k) {
  while (!node->leaf) {
    node = node->children.front();
    ++(*k);
  }
  int64_t val = node->keys.front();
  node->keys.erase(node->keys.begin());
  ++(*k);
  return val;
}

size_t BTree::deleteMerge(BTreeNode* node, int64_t i) {
  size_t k = 0;
  BTreeNode* left = node->children[i];
  BTreeNode* right = node->children[i + 1];

  left->keys.push_back(node->keys[i]);
  left->keys.insert(left->keys.end(), right->keys.begin(), right->keys.end());
  k += 2;
  if (!left->leaf) {
    left->children.insert(left->children.end(), right->children.begin(), 
      right->children.end());
    ++k;
  }

  node->keys.erase(node->keys.begin() + i);
  node->children.erase(node->children.begin() + i + 1);
  k += 2;
  delete right;
  return k;
}
