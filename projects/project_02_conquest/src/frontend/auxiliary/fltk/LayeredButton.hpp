// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_Button.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_RGB_Image.H> 

#include <vector>
#include <functional>

/// @brief Represents a button with multiple layers of PNG's
class LayeredButton : public Fl_Button {
 private:
  /// @brief Vector of layers (images)
  std::vector<Fl_Image*> layers;
  /// @brief Callback function triggered when the planet is clicked.
  std::function<void()> onClick;

 public:
  LayeredButton(int x, int y, int w, int h);   // Constructor
  ~LayeredButton();  // Destructor

  /// @brief Sets layer for button representation
  /// @param index The index to place the layer in
  /// @param img The image to add as layer
  void setLayer(size_t index, Fl_Image* img);

  /// @brief Removes a layer from the button
  /// @param index Indicates layer to remove
  void clearLayer(size_t index);

  /// @brief Removes all layers and redraws.
  void clearAllLayers();
 /**
  * @brief Assigns a callback function to be triggered on click.
  * @param func The function to call when the slot is clicked.
  */
  void setOnClick(std::function<void()> func);

 protected:
  /// @brief Overriden draw function to include layers, in order
  void draw() override;
};
