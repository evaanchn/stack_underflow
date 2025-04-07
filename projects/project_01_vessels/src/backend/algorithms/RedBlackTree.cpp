// Copyright 2025 stack_underflow CC-BY 4.0

#include "RedBlackTree.hpp"

redBlackTree::redBlackTree() : algorithm() {
  algorithmName = "Red Black Tree";
}

size_t redBlackTree::insert(int64_t element) {
  Node* newNode;
  newNode->value = element;
  newNode->leftChild = NIL;
  newNode->rightChild = NIL;
  Node* parent = nullptr;
  Node* current = root;
  while (current != NIL) {
    parent = current;
    if (newNode->value < current->value) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }
  newNode->parent = parent;
  if (parent == nullptr) {
    root = newNode;
  } else if (newNode->value < parent->value) {
    parent->leftChild = newNode;
  } else {
    parent->rightChild = newNode;
  }
  insertFixup(newNode);
}

size_t redBlackTree::search(int64_t element) {
  size_t interactions = 0;
  Node* node = root;
  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++interactions;
  }
  return interactions;
}

size_t redBlackTree::remove(int64_t element) {
  size_t interactions = 0;
  Node* node = root;
  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++interactions;
  }
  if (node == NIL) {
    std::cout << "Key not found!" << std::endl;
    return;
  }
  Node* y = node;
  std::string originalColor = y->color;
  Node* x;
  if (node->leftChild == NIL) {
    x = node->rightChild;
    transplant(node, node->rightChild);
  } else if (node->rightChild == NIL) {
    x = node->leftChild;
    transplant(node, node->leftChild);
  } else {
    y = minimum(node->rightChild, &interactions);
    originalColor = y->color;
    x = y->rightChild;

    if (y->parent == node) {
      x->parent = y;
    } else {
      transplant(y, y->rightChild);
      y->rightChild = node->rightChild;
      y->rightChild->parent = y;
    }
    transplant(node, y);
    y->leftChild = node->leftChild;
    y->leftChild->parent = y;
    y->color = node->color;
  }
  if (originalColor == "BLACK") {
    deleteFixup(x);
  }
  return interactions;
}

size_t redBlackTree::leftRotate(Node* node) {
  Node* rightChild = node->rightChild;
  node->rightChild = rightChild->leftChild;
  if (rightChild->leftChild != NIL) {
    rightChild->leftChild->parent = node;
  }
  rightChild->parent = node->parent;
  if (node->parent == nullptr) {
    root = rightChild;
  } else if (node == node->parent->leftChild) {
    node->parent->leftChild = rightChild;
  } else {
    node->parent->rightChild = rightChild;
  }
  rightChild->leftChild = node;
  node->parent = rightChild;
}

size_t redBlackTree::rightRotate(Node* node) {
  Node* leftChild = node->leftChild;
  node->leftChild = leftChild->rightChild;
  if (leftChild->rightChild != NIL) {
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

size_t redBlackTree::insertFixup(Node* node) {
  while (node->parent != nullptr && node->parent->color == "RED") {
    if (node->parent == node->parent->parent->leftChild) {
      Node* uncle = node->parent->parent->rightChild;
      if (uncle->color == "RED") {
        node->parent->color = "BLACK";
        uncle->color = "BLACK";
        node->parent->parent->color = "RED";
        node = node->parent->parent;
      } else {
        if (node == node->parent->rightChild) {
          node = node->parent;
          leftRotate(node);
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";
        rightRotate(node->parent->parent);
      }
    } else {
      Node* uncle = node->parent->parent->leftChild;
      if (uncle->color == "RED") {
        node->parent->color = "BLACK";
        uncle->color = "BLACK";
        node->parent->parent->color = "RED";
        node = node->parent->parent;
      } else {
        if (node == node->parent->leftChild) {
          node = node->parent;
          rightRotate(node);
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";
        leftRotate(node->parent->parent);
      }
    }
  }
  root->color = "BLACK";
}

size_t redBlackTree::deleteFixup(Node* node) {
  while (node != root && node->color == "BLACK") {
    if (node == node->parent->leftChild) {
      Node* sibling = node->parent->rightChild;
      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";
        leftRotate(node->parent);
        sibling = node->parent->rightChild;
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;
      } else {
        if (sibling->rightChild->color == "BLACK") {
          sibling->leftChild->color = "BLACK";
          sibling->color = "RED";
          rightRotate(sibling);
          sibling = node->parent->rightChild;
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->rightChild->color = "BLACK";
        leftRotate(node->parent);
        node = root;
      }
    } else {
      Node* sibling = node->parent->leftChild;
      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";
        rightRotate(node->parent);
        sibling = node->parent->leftChild;
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;
      } else {
        if (sibling->leftChild->color == "BLACK") {
          sibling->rightChild->color = "BLACK";
          sibling->color = "RED";
          leftRotate(sibling);
          sibling = node->parent->leftChild;
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->leftChild->color = "BLACK";
        rightRotate(node->parent);
        node = root;
      }
    }
  }
  node->color = "BLACK";
}

size_t redBlackTree::transplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->leftChild) {
    u->parent->leftChild = v;
  } else {
    u->parent->rightChild = v;
    v->parent = u->parent;
  }
}

Node* redBlackTree::minimum(Node* node, size_t* interactions) {
  while (node->leftChild != NIL) {
    node = node->leftChild;
    ++(*interactions);
  }
  return node;
}
