// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <math.h>

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// (Adapted from past projects)

/**
 * @brief A class that represents a customizable button with text and rounded corners.
 *
 * This class allows you to create a button with configurable size, position, text, color, and rounded corners.
 * It also provides functions to detect mouse hover and manipulate button properties.
 */
class Button {
 public:
  /**
   * @brief Constructs a button with specified text, background, size, and appearance properties.
   *
   * Initializes the button with a background color, text (label), position, size, corner radius, text size,
   * and text color.
   *
   * @param label The text to be displayed on the button.
   * @param filePath The file path to the font for the button text.
   * @param buttonColor The background color of the button.
   * @param size The size of the button (width and height).
   * @param position The position of the button on the window (X and Y coordinates).
   * @param radius The radius of the button's rounded corners.
   * @param cornerPoints The number of points used to draw the rounded corners.
   * @param labelSize The size of the text displayed on the button.
   * @param labelColor The color of the text.
   *
   * @note Throws an exception if the font file cannot be loaded.
   */
  Button(const std::string& label, const std::string& filePath
      , const sf::Color& buttonColor, const sf::Vector2f& size
      , const sf::Vector2f& position, float radius, int cornerPoints
      , unsigned int labelSize, const sf::Color& labelColor);

  /**
   * @brief Default constructor.
   *
   * Creates an empty button object with no predefined properties.
   */
  Button() = default;

  /**
   * @brief Draws the button on the provided SFML window.
   *
   * Renders the button and its text to the given SFML render window.
   *
   * @param window The SFML window where the button will be drawn.
   */
  void draw(sf::RenderWindow& window);

  /**
   * @brief Gets the position of the button.
   *
   * @return The current position of the button (X and Y coordinates).
   */
  sf::Vector2f getPosition() const;

  /**
   * @brief Gets the size of the button.
   *
   * @return The size of the button (width and height).
   */
  sf::Vector2f getSize() const;

  /**
   * @brief Gets the color of the button.
   *
   * @return The current background color of the button.
   */
  sf::Color getColor() const;

  /**
   * @brief Gets the text displayed on the button.
   *
   * @return The text currently displayed on the button.
   */
  std::string getText() const;

  /**
   * @brief Sets the position of the button.
   *
   * Updates the position of the button on the screen.
   *
   * @param position The new position of the button (X and Y coordinates).
   */
  void setPosition(const sf::Vector2f& position);

  /**
   * @brief Sets the size of the button.
   *
   * Updates the size of the button.
   *
   * @param size The new size of the button (width and height).
   */
  void setSize(const sf::Vector2f& size);

  /**
   * @brief Sets the background color of the button.
   *
   * Changes the color of the button.
   *
   * @param color The new background color for the button.
   */
  void setColor(const sf::Color& color);

  /**
   * @brief Sets the text displayed on the button.
   *
   * Updates the text content of the button.
   *
   * @param label The new text to display on the button.
   */
  void setLabel(const std::string& label);

  /**
   * @brief Sets the size of the text on the button.
   *
   * Updates the font size of the text displayed on the button.
   *
   * @param size The new size of the label.
   */
  void setLabelSize(unsigned int size);

  /**
   * @brief Sets the color of the text on the button.
   *
   * Changes the color of the button text.
   *
   * @param color The new color for the text.
   */
  void setLabelColor(const sf::Color& color);

  /**
   * @brief Checks if the mouse is currently over the button.
   *
   * @param window The SFML window where the button is displayed.
   * @return true if the mouse is hovering over the button, false otherwise.
   */
  bool isMouseOver(sf::RenderWindow& window) const;

 private:
  /**
   * @brief The font used for the text displayed on the button.
   */
  sf::Font font;

  /**
   * @brief The text displayed on the button: the label
   */
  sf::Text labelText;

  /**
   * @brief The vertex array used to render the rounded rectangle shape of the button.
   */
  sf::VertexArray shape;

  /**
   * @brief The color of the button's text.
   */
  sf::Color labelColor;

  /**
   * @brief Creates an arc for the button's rounded corners.
   *
   * This helper function is used to draw the rounded corners of the button.
   *
   * @param vertices The vertex array to store the points of the arc.
   * @param center The center point of the arc.
   * @param radius The radius of the arc.
   * @param startAngle The starting angle of the arc.
   * @param endAngle The ending angle of the arc.
   * @param points The number of points used to create the arc.
   * @param color The color of the arc.
   */
  void createArc(sf::VertexArray& vertices, sf::Vector2f center, float radius
      , float startAngle, float endAngle, int points, const sf::Color& color);

  /**
   * @brief Creates a rounded rectangle shape for the button.
   *
   * This helper function is used to draw the button's shape with rounded corners.
   *
   * @param vertices The vertex array to store the points of the shape.
   * @param position The position of the button.
   * @param size The size of the button.
   * @param radius The radius of the corners.
   * @param cornerPoints The number of points used to draw the rounded corners.
   * @param color The color of the button.
   */
  void createRoundedRectangle(sf::VertexArray& vertices, sf::Vector2f position
      , sf::Vector2f size, float radius, int cornerPoints
      , const sf::Color& color);

  /**
   * @brief Centers the text within the button.
   *
   * This helper function adjusts the position of the text to ensure it's centered within the button.
   *
   * @param position The position of the button.
   * @param buttonSize The size of the button.
   */
  void centerLabelInButton(const sf::Vector2f& position
      , const sf::Vector2f& buttonSize);

  /**
   * @brief Truncates the text if it exceeds the button size.
   *
   * This function shortens the text if it's too long to fit within the button's boundaries.
   *
   * @param text The text to be truncated.
   * @param buttonSize The size of the button.
   * @param textSize The size of the text.
   * @return The truncated text.
   */
  std::string truncateTextToFit(const std::string& text
      , const sf::Vector2f& buttonSize, unsigned int textSize);
};
