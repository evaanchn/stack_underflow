// Copyright 2025 stack_underflow CC-BY 4.0

#include "LinkedList.hpp"

LinkedList::LinkedList() {
  head = nullptr;
  tail = nullptr;
  algorithmName = "Linear Search";
}

bool LinkedList::listEmpty() {
  return head == nullptr && tail == nullptr;
}

LinkedList::Node* LinkedList::createNode(int64_t element) {
  Node *newNode = new Node;
  newNode->value = element;
  newNode->next = nullptr;
  return newNode;
}

LinkedList::~LinkedList() {
  while (!listEmpty()) popFront();
}

size_t LinkedList::insert(int64_t element) {
  Node *newNode = createNode(element);

  if (listEmpty()) {
    head = tail = newNode;
  } else {
    tail -> next = newNode;
    tail = newNode;
  }

  elementRecord.emplace(element);

  return 1;
}

// Linear search algorithm
size_t LinkedList::search(int64_t element) {
  size_t iterations = 0;
  if (!listEmpty()) {
    // If there's only one element in the list
    if (head->next == nullptr) {
      iterations = 1;  // o(1) search
    } else {
      bool found = false;
      Node * current = head;
      // Start from head, move forward until finding element
      while (current != nullptr && !found) {
        if (current->value == element) found = true;
        else
          current = current -> next;
        iterations += 1;  // Must increase in every iteration
      }
    }
  }
  return iterations;
}

// Linearly search for element and eliminate from list
size_t LinkedList::remove(int64_t eliminatingElement) {
  size_t repetitions = 0;
  if (!listEmpty() &&
      elementRecord.find(eliminatingElement) != elementRecord.end()) {
    // If there's only one element in the list or if head's value is the elem
    // to eliminate
    if (head->next == nullptr || head->value == eliminatingElement) {
      repetitions = popFront();
    } else {
      bool eliminated = false;
      Node* prev = head;
      Node* current = head->next;
      // Loop to find and eliminate
      while (current != nullptr && !eliminated) {
        if (current->value == eliminatingElement) {
          prev->next = current->next;  // Connects prev with new next
          delete current;  // eliminate node with requested value
          eliminated = true;  // To prevent iterating until the end
        } else {
          prev = current;
          current = current->next;
        }
        ++repetitions;
      }
    }
    elementRecord.erase(eliminatingElement);  // Remove from record
  } else {
    return 0;
  }
  return repetitions;
}

// For eliminating at head
size_t LinkedList::popFront() {
  size_t repetitions = 0;
  if (!listEmpty()) {
    Node * temp = head;
    head = head -> next;

    // If there was one element in list
    if (head == nullptr) tail = nullptr;

    delete temp;
    ++repetitions;
  }
  return repetitions;
}
