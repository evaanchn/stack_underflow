// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

//(Adapted from past projects)

/**
 * @brief A class that encapsulates image rendering functionality using SFML.
 *
 * This class provides the ability to load an image from a file, position it on the screen,
 * and render it on an SFML window.
 */
class SFMLImage {
public:
    /**
     * @brief Constructs an image object with the specified file path, position, and size.
     *
     * Loads an image from the provided file path and initializes the sprite with the given position and size.
     *
     * @param filePath The path to the image file to be loaded.
     * @param position The position of the image on the screen.
     * @param size The size of the image on the screen.
     *
     * @note Throws an exception if the image file cannot be loaded.
     */
    SFMLImage(const std::string& filePath, const sf::Vector2f& position, const sf::Vector2f& size);

    /**
     * @brief Default constructor.
     *
     * Creates an empty image object without any predefined properties.
     */
    SFMLImage() = default;

    /**
     * @brief Draws the image on the provided SFML window.
     *
     * Renders the image to the given SFML render window.
     *
     * @param window The SFML window where the image will be drawn.
     */
    void draw(sf::RenderWindow& window);

private:
    /**
     * @brief The texture that holds the image data.
     *
     * This stores the texture loaded from the image file.
     */
    sf::Texture texture;

    /**
     * @brief The sprite used to render the texture.
     *
     * The sprite holds the texture and provides the necessary properties like position and size for rendering.
     */
    sf::Sprite sprite;
};
