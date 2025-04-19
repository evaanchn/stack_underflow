// Copyright 2025 stack_underflow CC-BY 4.0

#include "HashsetVessel.hpp"

HashsetVessel::HashsetVessel()
: Vessel("Lightning", /* Health */ 50, /* Cost */ 200, /* Weight */ 5) {
  this->algorithm = new Hashset();
}
