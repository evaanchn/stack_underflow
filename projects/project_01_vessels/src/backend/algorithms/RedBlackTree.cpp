// Copyright 2025 stack_underflow CC-BY 4.0

#include "RedBlackTree.hpp"

redBlackTree::redBlackTree() : algorithm() {
  algorithmName = "Red Black Tree";
  NIL = new Node();
  NIL->color = "BLACK";
  NIL->leftChild = nullptr;
  NIL->rightChild = nullptr;
  NIL->parent = nullptr;
  root = NIL;
}

size_t redBlackTree::insert(int64_t element) {
  size_t interactions = 0;
  Node* newNode = new Node();
  newNode->value = element;
  newNode->leftChild = NIL;
  newNode->rightChild = NIL;
  Node* parent = nullptr;
  Node* current = root;
  interactions += 5;  // save interactions

  while (current != NIL) {
    parent = current;
    ++interactions;  // save interactions

    if (newNode->value < current->value) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
    ++interactions;  // save interactions
  }

  newNode->parent = parent;
  ++interactions;  // save interactions

  if (parent == nullptr) {
    root = newNode;
  } else if (newNode->value < parent->value) {
    parent->leftChild = newNode;
  } else {
    parent->rightChild = newNode;
  }
  ++interactions;  // save interactions

  interactions += insertFixup(newNode);  // save interactions
  return interactions;
}

size_t redBlackTree::search(int64_t element) {
  size_t interactions = 0;
  Node* node = root;
  ++interactions;  // save interactions

  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++interactions;  // save interactions
  }
  return interactions;
}

size_t redBlackTree::remove(int64_t element) {
  size_t interactions = 0;
  Node* node = root;
  ++interactions;  // save interactions

  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++interactions;  // save interactions
  }
  if (node == NIL) {
    std::cout << "Key not found!" << std::endl;
    return interactions;
  }

  Node* y = node;
  std::string originalColor = y->color;
  Node* x;
  interactions += 3;  // save interactions

  if (node->leftChild == NIL) {
    x = node->rightChild;
    ++interactions;  // save interactions

    interactions += transplant(node, node->rightChild);  // save interactions
  } else if (node->rightChild == NIL) {
    x = node->leftChild;
    ++interactions;  // save interactions

    interactions += transplant(node, node->leftChild);  // save interactions
  } else {
    y = minimum(node->rightChild, &interactions);
    originalColor = y->color;
    x = y->rightChild;
    interactions += 3;  // save interactions

    if (y->parent == node) {
      x->parent = y;
      ++interactions;  // save interactions
    } else {
      interactions += transplant(y, y->rightChild);  // save interactions
      y->rightChild = node->rightChild;
      y->rightChild->parent = y;
      interactions += 2;  // save interactions
    }
    interactions += transplant(node, y);  // save interactions
    y->leftChild = node->leftChild;
    y->leftChild->parent = y;
    y->color = node->color;
    interactions += 3;  // save interactions
  }
  if (originalColor == "BLACK") {
    interactions += deleteFixup(x);  // save interactions
  }
  return interactions;
}

size_t redBlackTree::leftRotate(Node* node) {
  size_t interactions = 0;
  Node* rightChild = node->rightChild;
  node->rightChild = rightChild->leftChild;
  interactions += 3;  // save interactions

  if (rightChild->leftChild != NIL) {
    rightChild->leftChild->parent = node;
    ++interactions;  // save interactions
  }

  rightChild->parent = node->parent;
  ++interactions;  // save interactions

  if (node->parent == nullptr) {
    root = rightChild;
  } else if (node == node->parent->leftChild) {
    node->parent->leftChild = rightChild;
  } else {
    node->parent->rightChild = rightChild;
  }
  ++interactions;  // save interactions

  rightChild->leftChild = node;
  node->parent = rightChild;
  interactions += 2;  // save interactions

  return interactions;
}

size_t redBlackTree::rightRotate(Node* node) {
  size_t interactions = 0;
  Node* leftChild = node->leftChild;
  node->leftChild = leftChild->rightChild;
  interactions += 2;  // save interactions

  if (leftChild->rightChild != NIL) {
    leftChild->rightChild->parent = node;
    ++interactions;  // save interactions
  }

  leftChild->parent = node->parent;
  ++interactions;  // save interactions

  if (node->parent == nullptr) {
    root = leftChild;
  } else if (node == node->parent->rightChild) {
    node->parent->rightChild = leftChild;
  } else {
    node->parent->leftChild = leftChild;
  }
  ++interactions;  // save interactions

  leftChild->rightChild = node;
  node->parent = leftChild;
  interactions += 2;  // save interactions

  return interactions;
}

size_t redBlackTree::insertFixup(Node* node) {
  size_t interactions = 0;
  while (node->parent != nullptr && node->parent->color == "RED") {
    if (node->parent == node->parent->parent->leftChild) {
      Node* uncle = node->parent->parent->rightChild;
      ++interactions;  // save interactions

      if (uncle->color == "RED") {
        node->parent->color = "BLACK";
        uncle->color = "BLACK";
        node->parent->parent->color = "RED";
        node = node->parent->parent;
        interactions += 4;  // save interactions

      } else {
        if (node == node->parent->rightChild) {
          node = node->parent;
          ++interactions;  // save interactions

          interactions += leftRotate(node);  // save interactions
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";
        interactions += 2;  // save interactions

        interactions += rightRotate(node->parent->parent);  // save interactions
      }
    } else {
      Node* uncle = node->parent->parent->leftChild;
      ++interactions;  // save interactions

      if (uncle->color == "RED") {
        node->parent->color = "BLACK";
        uncle->color = "BLACK";
        node->parent->parent->color = "RED";
        node = node->parent->parent;
        interactions += 4;  // save interactions

      } else {
        if (node == node->parent->leftChild) {
          node = node->parent;
          ++interactions;  // save interactions

          interactions += rightRotate(node);  // save interactions
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";
        interactions += 2;  // save interactions

        interactions += leftRotate(node->parent->parent);  // save interactions
      }
    }
  }
  root->color = "BLACK";
  ++interactions;  // save interactions
  return interactions;
}

size_t redBlackTree::deleteFixup(Node* node) {
  size_t interactions = 0;
  while (node != root && node->color == "BLACK") {
    if (node == node->parent->leftChild) {
      Node* sibling = node->parent->rightChild;
      ++interactions;  // save interactions

      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";
        interactions += 2;  // save interactions

        interactions += leftRotate(node->parent);  // save interactions

        sibling = node->parent->rightChild;
        ++interactions;  // save interactions
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;
        interactions += 2;  // save interactions

      } else {
        if (sibling->rightChild->color == "BLACK") {
          sibling->leftChild->color = "BLACK";
          sibling->color = "RED";
          interactions += 2;  // save interactions

          interactions += rightRotate(sibling);  // save interactions

          sibling = node->parent->rightChild;
          ++interactions;  // save interactions
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->rightChild->color = "BLACK";
        interactions += 3;  // save interactions

        interactions += leftRotate(node->parent);  // save interactions

        node = root;
        ++interactions;  // save interactions
      }
    } else {
      Node* sibling = node->parent->leftChild;
      ++interactions;  // save interactions

      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";
        interactions += 2;  // save interactions

        interactions += rightRotate(node->parent);  // save interactions

        sibling = node->parent->leftChild;
        ++interactions;  // save interactions
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;
        interactions += 2;  // save interactions
      } else {
        if (sibling->leftChild->color == "BLACK") {
          sibling->rightChild->color = "BLACK";
          sibling->color = "RED";
          interactions += 2;  // save interactions

          interactions += leftRotate(sibling);  // save interactions

          sibling = node->parent->leftChild;
          ++interactions;  // save interactions
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->leftChild->color = "BLACK";
        interactions += 3;  // save interactions

        interactions += rightRotate(node->parent);  // save interactions

        node = root;
        ++interactions;  // save interactions
      }
    }
  }
  node->color = "BLACK";
  ++interactions;  // save interactions

  return interactions;
}

size_t redBlackTree::transplant(Node* u, Node* v) {
  size_t interactions = 0;
  if (u->parent == nullptr) {
    root = v;
    ++interactions;  // save interactions
  } else if (u == u->parent->leftChild) {
    u->parent->leftChild = v;
    ++interactions;  // save interactions
  } else {
    u->parent->rightChild = v;
    v->parent = u->parent;
    interactions += 2;  // save interactions
  }
  return interactions;
}

Node* redBlackTree::minimum(Node* node, size_t* interactions) {
  while (node->leftChild != NIL) {
    node = node->leftChild;
    ++(*interactions);
  }
  return node;
}
