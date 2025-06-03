// Copyright 2025 stack_underflow CC-BY 4.0

#include "Button.hpp"

Button::Button(const std::string& label, const std::string& filePath,
    const sf::Color& buttonColor, const sf::Vector2f& size,
    const sf::Vector2f& position, float radius, int cornerPoints,
    unsigned int labelSize, const sf::Color& labelColor) {
  if (!font.loadFromFile(filePath)) {
    throw std::runtime_error("BUTTON ERROR: Font could not be loaded");
  }

  //TriangleFan for rounded corner buttons
  shape.setPrimitiveType(sf::TriangleFan);
  createRoundedRectangle(shape, position, size, radius,
      cornerPoints, buttonColor);

  labelText.setFont(font);
  labelText.setFillColor(labelColor);
  labelText.setCharacterSize(labelSize);

  std::string truncatedText = truncateTextToFit(label, size, labelSize);
  labelText.setString(truncatedText);

  centerLabelInButton(position, size);

  this->labelColor = labelColor;
}

std::string Button::truncateTextToFit(const std::string& content,
    const sf::Vector2f& buttonSize, unsigned int textSize) {
  sf::Text tempText;
  tempText.setFont(font);
  tempText.setCharacterSize(textSize);

  std::string truncatedText = content;
  while (true) {
    tempText.setString(truncatedText);
    if (tempText.getLocalBounds().width <= buttonSize.x * 0.9f &&
        tempText.getLocalBounds().height <= buttonSize.y * 0.9f) {
        break;
    }
    if (truncatedText.length() > 0) {
        truncatedText.pop_back();
    } else {
        break;
    }
  }
  return truncatedText;
}

void Button::centerLabelInButton(const sf::Vector2f& position,
    const sf::Vector2f& buttonSize) {
  sf::FloatRect textRect = labelText.getLocalBounds();
  labelText.setOrigin(textRect.left + textRect.width / 2.0f,
      textRect.top + textRect.height / 2.0f);
  labelText.setPosition(position.x + buttonSize.x / 2.0f,
      position.y + buttonSize.y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) {
  window.draw(shape);
  window.draw(labelText);
}

sf::Vector2f Button::getPosition() const {
  return sf::Vector2f(shape[0].position.x, shape[0].position.y);
}

sf::Vector2f Button::getSize() const {
  return sf::Vector2f(shape[1].position.x - shape[0].position.x,
      shape[2].position.y - shape[1].position.y);
}

sf::Color Button::getColor() const {
  return shape[0].color;
}

std::string Button::getText() const {
  return labelText.getString();
}

void Button::setPosition(const sf::Vector2f& position) {
  sf::Vector2f size = getSize();
  float radius = 20.f;
  int cornerPoints = 20;
  sf::Color color = getColor();
  shape.clear();
  createRoundedRectangle(shape, position, size, radius, cornerPoints, color);
  centerLabelInButton(position, size);
}

void Button::setSize(const sf::Vector2f& size) {
  sf::Vector2f position = getPosition();
  float radius = 20.f;
  int cornerPoints = 20;
  sf::Color color = getColor();
  shape.clear();
  createRoundedRectangle(shape, position, size, radius, cornerPoints, color);
  std::string truncatedText = truncateTextToFit(getText(),
      size, labelText.getCharacterSize());
  labelText.setString(truncatedText);
  centerLabelInButton(position, size);
}

void Button::setColor(const sf::Color& color) {
  for (size_t i = 0; i < shape.getVertexCount(); ++i) {
    shape[i].color = color;
  }
}

void Button::setLabel(const std::string& texto) {
  std::string truncatedText = truncateTextToFit(texto, getSize(),
      labelText.getCharacterSize());
  labelText.setString(truncatedText);
  centerLabelInButton(getPosition(), getSize());
}

void Button::setLabelSize(unsigned int size) {
  labelText.setCharacterSize(size);
  std::string truncatedText = truncateTextToFit(getText(), getSize(), size);
  labelText.setString(truncatedText);
  centerLabelInButton(getPosition(), getSize());
}

void Button::setLabelColor(const sf::Color& color) {
  labelColor = color;
  labelText.setFillColor(labelColor);
}

void Button::createArc(sf::VertexArray& vertices, sf::Vector2f center,
  float radius, float startAngle, float endAngle, int points,
  const sf::Color& color) {
  for (int i = 0; i <= points; ++i) {
    float angle = startAngle + (endAngle - startAngle) * i / points;
    sf::Vector2f point = center +
        sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius);
    vertices.append(sf::Vertex(point, color));
  }
}

void Button::createRoundedRectangle(sf::VertexArray& vertices,
    sf::Vector2f position, sf::Vector2f size, float radius,
    int cornerPoints, const sf::Color& color) {
  createArc(vertices, position + sf::Vector2f(radius, radius), radius, 3.14159f, 3.14159f / 2, cornerPoints, color);
  createArc(vertices, position + sf::Vector2f(size.x - radius, radius), radius, 3.14159f / 2, 0, cornerPoints, color);
  createArc(vertices, position + sf::Vector2f(size.x - radius, size.y - radius), radius, 0, -3.14159f / 2, cornerPoints, color);
  createArc(vertices, position + sf::Vector2f(radius, size.y - radius), radius, -3.14159f / 2, -3.14159f, cornerPoints, color);

  vertices.append(sf::Vertex(position + sf::Vector2f(radius, size.y), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(size.x - radius, size.y), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(size.x, size.y - radius), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(size.x, radius), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(size.x - radius, 0), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(radius, 0), color));
  vertices.append(sf::Vertex(position + sf::Vector2f(0, radius), color));
}

bool Button::isMouseOver(sf::RenderWindow& window) const {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  sf::FloatRect boundingBox = shape.getBounds(); 
  return boundingBox.contains(static_cast<sf::Vector2f>(mousePos));
}