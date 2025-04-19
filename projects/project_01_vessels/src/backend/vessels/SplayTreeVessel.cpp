// Copyright 2025 stack_underflow CC-BY 4.0

#include "SplayTreeVessel.hpp"

SplayTreeVessel::SplayTreeVessel()
: Vessel("Ratatosk", /* Health */ 150, /* Cost */ 30, /* Weight */ 2) {
  this->algorithm = new SplayTree();
}
