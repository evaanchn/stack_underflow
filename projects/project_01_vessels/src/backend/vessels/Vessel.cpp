// Copyright 2025 stack_underflow CC-BY 4.0

#include "Vessel.hpp"

Vessel::Vessel(std::string nameInit, int64_t healthInit, size_t costInit
    , size_t weightInit)
: name(nameInit)
, health(healthInit)
, cost(costInit)
, weight(weightInit) {
}

void Vessel::takeDamage(int64_t damage_dealed) {
  if (this->isAlive()) {
    this->health -= damage_dealed;
  }
}

bool Vessel::isAlive() {
  return (this->health > 0);
}
