// Copyright 2025 stack_underflow CC-BY 4.0

#include "RedBlackTreeVessel.hpp"

RedBlackTreeVessel::RedBlackTreeVessel()
: Vessel("Ragnalog", /* Health */ 80, /* Cost */ 150, /* Weight */ 3) {
  this->algorithm = new RedBlackTree();
}
