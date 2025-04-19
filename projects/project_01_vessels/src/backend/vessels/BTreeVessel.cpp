// Copyright 2025 stack_underflow CC-BY 4.0

#include "BTreeVessel.hpp"

BTreeVessel::BTreeVessel()
: Vessel("Thunder", /* Health */ 120, /* Cost */ 50, /* Weight */ 2) {
  this->algorithm = new BTree(MINIMUM_GRADE);
}
