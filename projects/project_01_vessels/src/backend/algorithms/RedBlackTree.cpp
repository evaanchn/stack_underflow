// Copyright 2025 stack_underflow CC-BY 4.0

#include "RedBlackTree.hpp"

RedBlackTree::RedBlackTree() : Algorithm() {
  algorithmName = "Red Black Tree";
  NIL = new Node();
  NIL->color = "BLACK";
  NIL->leftChild = nullptr;
  NIL->rightChild = nullptr;
  NIL->parent = nullptr;
  root = NIL;
}

RedBlackTree::~RedBlackTree() {
  clear();
  delete NIL;
  NIL = nullptr;
  elementRecord.clear();
}

void RedBlackTree::clear() {
  if (this->root == nullptr) return;
  std::stack<Node*> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    Node* current = nodes.top();
    nodes.pop();

    if (current->leftChild && current->leftChild != NIL) {
      nodes.push(current->leftChild);
    }
    if (current->rightChild && current->rightChild != NIL) {
      nodes.push(current->rightChild);
    }
    delete current;
  }
  root = nullptr;
}

size_t RedBlackTree::insert(int64_t element) {
  if (elementRecord.find(element) != elementRecord.end()) {
    return 0;
  }
  size_t k = 0;
  Node* newNode = new Node();
  newNode->value = element;
  newNode->leftChild = NIL;
  newNode->rightChild = NIL;
  Node* parent = nullptr;
  Node* current = root;
  ++k;  // save interactions

  while (current != NIL) {
    parent = current;
    if (newNode->value < current->value) {
      current = current->leftChild;
    } else {
      current = current->rightChild;
    }
  }
  ++k;  // save interactions

  newNode->parent = parent;

  if (parent == nullptr) {
    root = newNode;
  } else if (newNode->value < parent->value) {
    parent->leftChild = newNode;
  } else {
    parent->rightChild = newNode;
  }
  ++k;  // save interactions

  k += insertFixup(newNode);  // save interactions
  elementRecord.insert(element);
  return k;
}

size_t RedBlackTree::search(int64_t element) {
  size_t k = 0;
  Node* node = root;

  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++k;  // save interactions
  }
  return k;
}

size_t RedBlackTree::remove(int64_t element) {
  if (elementRecord.find(element) == elementRecord.end()) {
    return 0;
  }
  size_t k = 0;
  Node* node = root;

  while (node != NIL && element != node->value) {
    if (element < node->value) {
      node = node->leftChild;
    } else {
      node = node->rightChild;
    }
    ++k;  // save interactions
  }
  if (node == NIL) {
    std::cout << "Key not found!" << std::endl;
    return k;
  }

  Node* y = node;
  std::string originalColor = y->color;
  Node* x;

  if (node->leftChild == NIL) {
    x = node->rightChild;
    k += transplant(node, node->rightChild);  // save interactions
  } else if (node->rightChild == NIL) {
    x = node->leftChild;
    k += transplant(node, node->leftChild);  // save interactions
  } else {
    y = minimum(node->rightChild, &k);
    originalColor = y->color;
    x = y->rightChild;
    ++k;  // save interactions

    if (y->parent == node) {
      x->parent = y;
    } else {
      k += transplant(y, y->rightChild);  // save interactions
      y->rightChild = node->rightChild;
      y->rightChild->parent = y;
    }
    ++k;  // save interactions
    k += transplant(node, y);  // save interactions
    y->leftChild = node->leftChild;
    y->leftChild->parent = y;
    y->color = node->color;
    ++k;  // save interactions
  }
  if (originalColor == "BLACK") {
    k += deleteFixup(x);  // save interactions
  }
  elementRecord.erase(element);
  return k;
}

size_t RedBlackTree::leftRotate(Node* node) {
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

  return 1;
}

size_t RedBlackTree::rightRotate(Node* node) {
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

  return 1;
}

size_t RedBlackTree::insertFixup(Node* node) {
  size_t k = 0;
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
          k += leftRotate(node);  // save interactions
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";

        k += rightRotate(node->parent->parent);  // save interactions
      }
      ++k;  // save interactions
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
          k += rightRotate(node);  // save interactions
        }
        node->parent->color = "BLACK";
        node->parent->parent->color = "RED";

        k += leftRotate(node->parent->parent);  // save interactions
      }
    }
  }
  root->color = "BLACK";
  ++k;  // save interactions
  return k;
}

size_t RedBlackTree::deleteFixup(Node* node) {
  size_t k = 0;
  while (node != root && node->color == "BLACK") {
    if (node == node->parent->leftChild) {
      Node* sibling = node->parent->rightChild;

      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";

        k += leftRotate(node->parent);  // save interactions

        sibling = node->parent->rightChild;
        ++k;  // save interactions
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;

      } else {
        if (sibling->rightChild->color == "BLACK") {
          sibling->leftChild->color = "BLACK";
          sibling->color = "RED";

          k += rightRotate(sibling);  // save interactions

          sibling = node->parent->rightChild;
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->rightChild->color = "BLACK";

        k += leftRotate(node->parent);  // save interactions

        node = root;
      }
      ++k;  // save interactions
    } else {
      Node* sibling = node->parent->leftChild;

      if (sibling->color == "RED") {
        sibling->color = "BLACK";
        node->parent->color = "RED";

        k += rightRotate(node->parent);  // save interactions

        sibling = node->parent->leftChild;
        ++k;  // save interactions
      }
      if (sibling->leftChild->color == "BLACK" && sibling->rightChild->color ==
        "BLACK") {
        sibling->color = "RED";
        node = node->parent;
      } else {
        if (sibling->leftChild->color == "BLACK") {
          sibling->rightChild->color = "BLACK";
          sibling->color = "RED";

          k += leftRotate(sibling);  // save interactions

          sibling = node->parent->leftChild;
        }
        sibling->color = node->parent->color;
        node->parent->color = "BLACK";
        sibling->leftChild->color = "BLACK";

        k += rightRotate(node->parent);  // save interactions

        node = root;
      }
      ++k;  // save interactions
    }
  }
  node->color = "BLACK";

  return k;
}

size_t RedBlackTree::transplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->leftChild) {
    u->parent->leftChild = v;
  } else {
    u->parent->rightChild = v;
  }
  v->parent = u->parent;  // Mover fuera del else
  return 1;
}

RedBlackTree::Node* RedBlackTree::minimum(Node* node, size_t* interactions) {
  while (node->leftChild != NIL) {
    node = node->leftChild;
    ++(*interactions);
  }
  return node;
}
