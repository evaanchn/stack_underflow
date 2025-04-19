// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//(Adapted from past projects)

/**
 * @brief A class representing a rectangle using SFML.
 *
 * This class encapsulates an SFML rectangle shape with configurable size, position,
 * and outline properties. It provides functionality to render the rectangle to a window.
 */
class SFMLRectangle {
public:
    /**
     * @brief Constructs a rectangle with specified dimensions and properties.
     *
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param x The X-coordinate of the rectangle's position.
     * @param y The Y-coordinate of the rectangle's position.
     * @param outlineThickness The thickness of the rectangle's outline.
     * @param outlineColor The color of the rectangle's outline.
     */
    SFMLRectangle(float width, float height, float x, float y, float outlineThickness, sf::Color outlineColor);

    /**
     * @brief Draws the rectangle on the given SFML window.
     *
     * @param window The SFML window where the rectangle will be drawn.
     */
    void draw(sf::RenderWindow& window);

private:
    /**
     * @brief The SFML rectangle shape.
     *
     * This stores the graphical representation of the rectangle, including its size, position,
     * outline, and color.
     */
    sf::RectangleShape rectangle;
};
