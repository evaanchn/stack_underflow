// Copyright 2025 stack_underflow CC-BY 4.0

#include "SFMLRectangle.hpp"

SFMLRectangle::SFMLRectangle(float width, float height, float x, float y, float outlineThickness, sf::Color outlineColor) {
  rectangle.setSize(sf::Vector2f(width, height));

  rectangle.setPosition(x, y);

  rectangle.setOutlineThickness(outlineThickness);

  rectangle.setOutlineColor(outlineColor);

  rectangle.setFillColor(sf::Color::Transparent);
}

void SFMLRectangle::draw(sf::RenderWindow& window) {
  window.draw(rectangle);
}
