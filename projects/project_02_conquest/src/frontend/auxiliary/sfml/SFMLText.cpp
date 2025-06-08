// Copyright 2025 stack_underflow CC-BY 4.0

#include "SFMLText.hpp"

SFMLText::SFMLText(const std::string& content, const std::string& fontPath,
    unsigned int characterSize, sf::Color color, sf::Vector2f position)
    : text(sf::Text()),
    font(sf::Font()),
    characterSize(characterSize),
    color(color),
    position(position) {
  if (!font.loadFromFile(fontPath)) {
    throw std::runtime_error("TEXT ERROR: Font could not be loaded");
  }

  text.setString(content);
  text.setFont(font);
  text.setCharacterSize(characterSize);
  text.setFillColor(color);
  text.setPosition(position);
}

void SFMLText::draw(sf::RenderWindow& window) {
  window.draw(text);
}

void SFMLText::setText(const std::string& newText) {
  text.setString(newText);
}

void SFMLText::setFont(const std::string& fontPath) {
  if (!font.loadFromFile(fontPath)) {
    throw std::runtime_error("TEXT ERROR: Font could not be loaded");
  }
  text.setFont(font);
}

void SFMLText::setCharacterSize(unsigned int size) {
  text.setCharacterSize(size);
}

void SFMLText::setColor(sf::Color newColor) {
  color = newColor;
  text.setFillColor(color);
}

void SFMLText::setPosition(sf::Vector2f newPosition) {
  position = newPosition;
  text.setPosition(position);
}
