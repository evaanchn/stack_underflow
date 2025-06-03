// Copyright 2025 stack_underflow CC-BY 4.0

#include "Boss.hpp"

void Boss::receiveDamage(int damagePoints) {
  this->healthPoints -= damagePoints;
}

int Boss::getHealth() const {
  return this->healthPoints;
}

bool Boss::isDead() const {
  return this->healthPoints > 0;
}

std::string Boss::toString() const {
  return "Health: " + std::to_string(this->healthPoints);
}
