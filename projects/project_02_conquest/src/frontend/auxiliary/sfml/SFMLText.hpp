// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// (Adapted from past projects)

/**
 * @brief A class that encapsulates text rendering functionality using SFML.
 *
 * This class provides methods to display text with configurable font, size, color, and position
 * on an SFML window.
 */
class SFMLText {
 public:
  /**
   * @brief Constructs a text object with specified properties.
   *
   * Initializes the SFML text object with the provided string, font, character size, color, and position.
   *
   * @param content The string to be displayed.
   * @param fontPath The path to the font file to be used.
   * @param characterSize The size of the characters in the text.
   * @param color The color of the text.
   * @param position The position of the text on the screen.
   *
   * @note Throws an exception if the font file cannot be loaded.
   */
  SFMLText(const std::string& content, const std::string& fontPath
      , unsigned int characterSize, sf::Color color, sf::Vector2f position);

  /**
   * @brief Default constructor.
   *
   * Creates an empty text object without any predefined properties.
   */
  SFMLText() = default;

  /**
   * @brief Draws the text on the provided SFML window.
   *
   * Renders the text to the given SFML render window.
   *
   * @param window The SFML window where the text will be drawn.
   */
  void draw(sf::RenderWindow& window);

  /**
   * @brief Sets the displayed text.
   *
   * Updates the string content of the text.
   *
   * @param newText The new string to display.
   */
  void setText(const std::string& newText);

  /**
   * @brief Sets the font of the text.
   *
   * Loads and sets a new font for the text.
   *
   * @param fontPath The path to the new font file.
   *
   * @note Throws an exception if the font file cannot be loaded.
   */
  void setFont(const std::string& fontPath);

  /**
   * @brief Sets the character size of the text.
   *
   * Updates the size of the characters in the text.
   *
   * @param size The new character size.
   */
  void setCharacterSize(unsigned int size);

  /**
   * @brief Sets the color of the text.
   *
   * Changes the color of the displayed text.
   *
   * @param newColor The new color for the text.
   */
  void setColor(sf::Color newColor);

  /**
   * @brief Sets the position of the text on the screen.
   *
   * Updates the position where the text will be rendered.
   *
   * @param newPosition The new position for the text.
   */
  void setPosition(sf::Vector2f newPosition);

 private:
  /**
   * @brief The SFML text object.
   *
   * This represents the actual text to be rendered on the screen.
   */
  sf::Text text;

  /**
   * @brief The font used by the text.
   *
   * This stores the font loaded from the font file to display the text.
   */
  sf::Font font;

  /**
   * @brief The size of the characters in the text.
   */
  unsigned int characterSize;

  /**
   * @brief The color of the text.
   */
  sf::Color color;

  /**
   * @brief The position of the text on the screen.
   */
  sf::Vector2f position;
};


