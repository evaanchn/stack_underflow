// Copyright 2025 stack_underflow CC-BY 4.0

#include "Planet.hpp"

Planet::Planet(std::string name, bool planetHasMine)
    : name(name)
    , planetHasMine(planetHasMine)
    , coordinates(nullptr)
    , boss(nullptr) {
  if (this->planetHasMine) this->spawnBoss();
}

Planet::~Planet() {
  if (this->boss) delete this->boss;
  if (this->coordinates) delete this->coordinates;
}

void Planet::setCoordinates(Coordinates* coordinates) {
  this->coordinates = coordinates;
}

void Planet::setMine() {
  this->planetHasMine = HAS_MINE;
}

void Planet::spawnBoss() {
  if (!this->boss) this->boss = new Boss();
}

void Planet::removeBoss() {
  if (this->boss) delete this->boss;
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

double Planet::getDistanceTo(Planet* planet) {
  // Use distance between points formula
  // x = col, y = row
  // Cast is necessary given size_t would have problems with negatives
  int rowDifference = static_cast<int>(this->coordinates->row)
      - static_cast<int>(planet->getCoordinates()->row);
  int colDifference = static_cast<int>(this->coordinates->col)
      - static_cast<int>(planet->getCoordinates()->col);

  double distance = std::sqrt(rowDifference * rowDifference
      + colDifference * colDifference);
  return distance;
}
