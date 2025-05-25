// Copyright 2025 stack_underflow CC-BY 4.0

#include "Planet.hpp"

Planet::Planet(std::string name, bool planetHasMine, Boss* boss
    , Coordinates* coordinates)
    : name(name)
    , planetHasMine(planetHasMine)
    , boss(boss)
    , coordinates(coordinates) {}

Planet::~Planet() {
  if (this->boss) delete this->boss;
  if (this->coordinates) delete this->coordinates;
}

void Planet::setCoordinates(Coordinates* coordinates) {
  this->coordinates = coordinates;
}

void Planet::spawnBoss() {
  this->boss = new Boss();
}

void Planet::defeatBoss() {
  delete this->boss;
  this->boss = nullptr;
}

bool Planet::hasBoss() const {
  return this->boss != nullptr;
}

bool Planet::hasMine() const {
  return this->planetHasMine;
}

Boss* Planet::getBoss() {
  return this->boss;
}

std::string Planet::getName() const {
  return this->name;
}

Coordinates* Planet::getCoordinates() const {
  return this->coordinates;
}

std::string Planet::toString() const {
  std::string bossData =  this->hasBoss() ? "Available ("
      + this->boss->toString() + ")" : "N/A";
  std::string mineData = this->planetHasMine ? "Available" : "N/A";
  return "Planet - " + this->name + "\nCoordinates - "
      + std::to_string(this->coordinates->row) + ", "
      + std::to_string(this->coordinates->col)
      + "\nBoss - " + bossData
      + "\nMine - " + mineData;
}
