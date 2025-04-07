// Copyright 2025 stack_underflow CC-BY 4.0

#include "Slot.hpp"

Slot::Slot()
: coordinates(2)
, occupied(false)
, vessel(nullptr) {
}

Slot::~Slot() {
  if (this->vessel != nullptr) delete this->vessel;
}

bool Slot::isOccupied() {
  return this->occupied;
}

Vessel* Slot::getVessel() {
  return this->vessel;
}

bool Slot::insertVessel(Vessel* newVessel) {
  if (this->isOccupied() || newVessel == nullptr) return false;
  this->vessel = newVessel;
  this->occupied = true;
  return true;
}

bool Slot::removeVessel() {
  if (!this->occupied) return false;
  this->vessel = nullptr;
  this->occupied = false;
  return true;
}

bool Slot::destroyVessel() {
  if (!this->occupied) return false;
  if (this->vessel != nullptr) delete this->vessel;
  this->vessel = nullptr;
  this->occupied = false;
  return true;
}
