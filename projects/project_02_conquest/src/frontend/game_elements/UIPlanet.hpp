// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_PNG_Image.H>
#include <string>

#include "LayeredButton.hpp"

#include "Random.hpp"
#include "Planet.hpp"

enum PLANET_LAYERS {
  SPHERE, TERRAIN, OCCUPIER
};

#define AVAILABLE_SPHERE_SPRITES 10
#define AVAILABLE_TERRAIN_SPRITES 10

const std::string SPRITES_PATH = "assets/sprites/";
const std::string SPHERE_PATH = SPRITES_PATH + "planet/sphere/";
const std::string TERRAIN_PATH = SPRITES_PATH + "planet/terrain/";
const std::string SPHERE_SPRITE = "planet";
const std::string TERRAIN_SPRITE = "planet";
const std::string SPRITES_EXTENSION = ".png";

/// @class UIPlanet
/// @brief Represents a planet using a layered FLTK button.
class UIPlanet {
 private:
  /// @brief The underlying FLTK layered button used to render the planet.
  LayeredButton* button = nullptr;
  size_t x;
  size_t y;
  size_t dimension;

 public:
  /// @brief Default constructor. Does not initialize the planet button.
  UIPlanet() = default;

  /// @brief Constructs a UIPlanet at a given position with specified size.
  /// @param x The x-coordinate of the planet's position.
  /// @param y The y-coordinate of the planet's position.
  /// @param dimension The width and height of the square-shaped planet button.
  explicit UIPlanet(size_t x, size_t y, size_t dimension
      , const char* planetName = nullptr);

  /// @brief Destructor. Cleans up dynamically allocated resources.
  ~UIPlanet();

 private:
  /// @brief Sets the appearance of the planet using sphere and terrain sprites.
  void setPlanetAppearance();

  /// @brief Constructs a file path to a random sprite from available.
  /// @param initialLayerPath The base path for the sprite layer.
  /// @param availableSprites The total number of available sprite variants.
  /// @return The complete path to a randomly selected sprite.
  std::string constructLayerPath(const std::string& initialLayerPath
      , int availableSprites);

 public:
  /// @brief Makes the planet visible and interactive in the UI.
  void reveal();

  /// @brief Sets an image layer to represent an occupier (e.g., unit or object)
  /// on the planet.
  /// @param occupier A pointer to a `Fl_PNG_Image` to be used as the occupier's
  /// image.
  void setOccupier(Fl_PNG_Image* occupier);

  /// @brief Removes the occupier image layer from the planet.
  void removeOccupier();

  /// @brief Assigns a function to execute when the planet is clicked.
  /// @param func The action the planet's button must carry out
  void setPlanetInteraction(std::function<void()> func);

  size_t getX() const;
  size_t getY() const;
  size_t getSize() const;
  Fl_Widget* getButton() { return this-> button; }
};
