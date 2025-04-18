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
  UISlot(int x, int y);
  ~UISlot();

  void setOnClick(std::function<void()> func);
  void deactivate();
  void setColor(Fl_Color color);

  void setVessel(Fl_PNG_Image* _vessel);
  Fl_PNG_Image* getVessel();
  void clearVessel();

  void setMask(Fl_PNG_Image* _mask);
  void showMask();
  void hideMask();

 private:
  Fl_Button* button;
  Fl_PNG_Image* vessel;  // Vessel that will be displayed in the slot
  Fl_PNG_Image* slotMask;  // Mask for the slot
  std::function<void()> onClick;
};
