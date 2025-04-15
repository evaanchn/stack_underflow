// Copyright 2025 stack_underflow CC-BY 4.0

#include "LinearSearchVessel.hpp"

LinearSearchVessel::LinearSearchVessel()
: Vessel("Caronte", 200, 10, 1) {
  this->algorithm = new LinkedList();
}
