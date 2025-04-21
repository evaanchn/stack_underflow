// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <functional>

#define SLOT_DIMENSION 100
const Fl_Color LIGHT_CELL = fl_rgb_color(3, 169, 244);  // Light blue
const Fl_Color DARK_CELL = fl_rgb_color(2, 136, 209);  // Dark blue

class UISlot {
 public:
  /**
   * @brief Constructs a UISlot at the specified position.
   * @param x The X-coordinate of the top-left corner.
   * @param y The Y-coordinate of the top-left corner.
   */
  UISlot(int x, int y);

  /**
   * @brief Destroys the UISlot and releases associated resources.
   */
  ~UISlot();

  /**
   * @brief Assigns a callback function to be triggered on click.
   * @param func The function to call when the slot is clicked.
   */
  void setOnClick(std::function<void()> func);

  /**
   * @brief Enables the slot, making it interactive.
   */
  void activate();

  /**
   * @brief Disables the slot, preventing interaction.
   */
  void deactivate();

  /**
   * @brief Sets the background color of the slot.
   * @param color The desired FLTK color.
   */
  void setColor(Fl_Color color);

  /**
   * @brief Sets the vessel image to display in the slot.
   * @param _vessel Pointer to the vessel image.
   */
  void setVessel(Fl_PNG_Image* _vessel);

  /**
   * @brief Gets the current vessel image set in the slot.
   * @return Pointer to the vessel image.
   */
  Fl_PNG_Image* getVessel();

  /**
   * @brief Clears the vessel image from the slot.
   */
  void clearVessel();

  /**
   * @brief Applies a mask image to the slot.
   * @param _mask Pointer to the mask image.
   */
  void setMask(Fl_PNG_Image* _mask);

  /**
   * @brief Shows the mask image over the slot.
   */
  void showMask();

  /**
   * @brief Hides the mask and shows the vessel (if any).
   */
  void hideMask();

 private:
  /**
   * @brief The underlying FLTK button representing the slot.
   */
  Fl_Button* button;

  /**
   * @brief The vessel image shown in the slot (if any).
   */
  Fl_PNG_Image* vessel;

  /**
   * @brief The mask image currently applied to the slot.
   */
  Fl_PNG_Image* slotMask;

  /**
   * @brief Callback function triggered when the slot is clicked.
   * In this case, it will be dumping the current slot's coordinates
   * to the corresponding Coordinates container
   */
  std::function<void()> onClick;
};
