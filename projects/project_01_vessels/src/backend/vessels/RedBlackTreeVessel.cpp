// Copyright 2025 stack_underflow CC-BY 4.0

#include "RedBlackTreeVessel.hpp"

RedBlackTreeVessel::RedBlackTreeVessel()
: Vessel("Ragnalog", 80, 150, 3) {
  this->algorithm = new RedBlackTree();
}
