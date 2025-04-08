// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <string>

#include "Algorithm.hpp"

struct Node {
  int64_t value;
  struct Node * next;
};

class LinkedList : public algorithm {
 public:
  LinkedList();
  ~LinkedList();
  size_t insert(int64_t element) override;
  size_t search(int64_t element) override;
  size_t remove(int64_t element) override;

 private:
  Node *head;
  Node *tail;

  bool listEmpty();
  Node* createNode(int64_t element);
  size_t popFront();
};

