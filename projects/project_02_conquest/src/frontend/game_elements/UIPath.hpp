// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#pragma once

#include <FL/fl_draw.H>
#include <memory>
#include <utility>

#include "UIPlanet.hpp"

/**
 * @class UIPath
 * @brief A widget that represents a visual path/connection between two UIPlanet objects
 * 
 * This class inherits from Fl_Widget and is used to display and manage the visual representation
 * of a path between two planets in the user interface, including its weight and color properties.
 */
class UIPath : public Fl_Widget {
 private:
  ///< Pointer to the first planet connected by this path
  UIPlanet* planetA = nullptr;
  ///< Pointer to the second planet connected by this path
  UIPlanet* planetB = nullptr;
  ///< Pointer to the second planet connected by this path  
  size_t weight = 0;
  ///< Color used to draw this path 
  Fl_Color color = 0;

 public:
  /**
   * @brief Construct a new UIPath object
   * @param a Pointer to the first UIPlanet
   * @param b Pointer to the second UIPlanet
   * @param weight Initial weight of the path (default: 0)
   * @param color Initial color of the path (default: FL_WHITE)
   */
  UIPath(UIPlanet* a, UIPlanet* b, size_t weight = 0
    , Fl_Color color = FL_WHITE);
  
  /// @brief Default constructor
  UIPath() = default;

  /**
   * @brief Draw the path on the FLTK widget
   * 
   * Overrides the Fl_Widget draw method to render the path between the two planets.
   */
  void draw() override;
  
  /**
   * @brief Make the path visible
   * 
   * Changes the path's appearance to make it visible in the UI.
   */
  void reveal();
  
  /**
   * @brief Set the weight of this path
   * @param newWeight The new weight value to set
   */
  void setWeight(size_t newWeight);
  
  /**
   * @brief Set the color of this path
   * @param newColor The new color to set (FL_Color value)
   */
  void setColor(Fl_Color newColor);
  
  /**
   * @brief Get the current weight of this path
   * @return int The current weight value
   */
  int getWeight() const;
  
  /**
   * @brief Get the planets connected by this path
   * @return std::pair<UIPlanet*, UIPlanet*> A pair containing pointers to the connected planets
   */
  std::pair<UIPlanet*, UIPlanet*> getPlanets() const;
};