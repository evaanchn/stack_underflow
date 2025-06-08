// Copyright 2025 stack_underflow CC-BY 4.0

#include "UIPlanet.hpp"

UIPlanet::UIPlanet(size_t x, size_t y, size_t dimension) {
  this->x = x;
  this->y = y;
  this->dimension = dimension;
  this->button = new LayeredButton(x, y, dimension, dimension);
  // this->button->deactivate();
  // this->button->hide();
  this->setPlanetAppearance();
}

UIPlanet::~UIPlanet() {
  if (this->button) delete this->button;
}

void UIPlanet::setPlanetAppearance() {
  std::string spherePath = constructLayerPath(SPHERE_PATH + SPHERE_SPRITE
      , AVAILABLE_SPHERE_SPRITES);
  std::string terrainPath = constructLayerPath(TERRAIN_PATH + TERRAIN_SPRITE
      , AVAILABLE_TERRAIN_SPRITES);
  // Create images and set to button in respective layers
  Fl_PNG_Image planetSphere = Fl_PNG_Image(spherePath.c_str());
  Fl_PNG_Image planetTerrain = Fl_PNG_Image(terrainPath.c_str());
  // Button will scale images inside
  this->button->setLayer(SPHERE, &planetSphere);
  this->button->setLayer(TERRAIN, &planetTerrain);
}

std::string UIPlanet::constructLayerPath(const std::string& initialLayerPath
      , int availableSprites) {
  // Generate a valid index between 1 and the max number of available sprites
  int spriteIndex = Random<int>().generateRandomInRange(1
      , availableSprites);
  // To string of index, with 0 or not as prefix for 1-9
  std::string spriteIndexStr = spriteIndex < 10 ? "0"
      + std::to_string(spriteIndex) : std::to_string(spriteIndex);
  // Construct path and return as c string
  return initialLayerPath + spriteIndexStr + SPRITES_EXTENSION;
}

void UIPlanet::reveal() {
  this->button->activate();
  this->button->show();
  this->button->redraw();
}

void UIPlanet::setOccupier(Fl_PNG_Image* occupier) {
  if (occupier) this->button->setLayer(OCCUPIER, occupier);
}

void UIPlanet::removeOccupier() {
  this->button->clearLayer(OCCUPIER);
}

void UIPlanet::setPlanetInteraction(std::function<void()> func) {
  this->button->setOnClick(func);
}

size_t UIPlanet::getX() const {
  return this->x;
}

size_t UIPlanet::getY() const {
  return this->y;
}

size_t UIPlanet::getSize() const {
  return this->dimension;
}
