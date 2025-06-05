// Copyright 2025 stack_underflow CC-BY 4.0

#include "SFMLImage.hpp"

SFMLImage::SFMLImage(const std::string& filePath,
    const sf::Vector2f& position, const sf::Vector2f& size) {
  if (!texture.loadFromFile(filePath)) {
    throw std::runtime_error("IMAGE ERROR: Texture could not be loaded");
  }

  sprite.setTexture(texture);
  sprite.setPosition(position);
  sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

void SFMLImage::draw(sf::RenderWindow& window) {
  window.draw(sprite);
}
