// Copyright 2025 stack_underflow CC-BY 4.0

#include "LinearSearchVessel.hpp"

LinearSearchVessel::LinearSearchVessel()
: Vessel("Harbinger", /* Health */ 200, /* Cost */ 10, /* Weight */ 1) {
  this->algorithm = new LinkedList();
}
