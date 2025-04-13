// Copyright 2025 stack_underflow CC-BY 4.0

#include "CustomIconButton.hpp"

CustomIconButton::CustomIconButton(int x, int y, int w, int h,
    const std::string& icon_path, const std::string& text)
  : Fl_Button(x, y, w, h),
  icon(nullptr),
  label_text(text),
  font_size(14),
  label_color(FL_WHITE) {
  icon = new Fl_PNG_Image(icon_path.c_str());
  box(FL_NO_BOX);           // Transparent background
  down_box(FL_NO_BOX);
  color(FL_BACKGROUND_COLOR);  // Not visible anyway
  label("");               // We draw our own label
  callback(StaticCallback, this); // FLTK requires static callbacks
}

void CustomIconButton::draw() {
  // Draw icon centered
  if (icon) {
    int ix = x() + (w() - icon->w()) / 2;
    int iy = y() + (h() - icon->h()) / 2;
    icon->draw(ix, iy);
  }

  // Draw label under or on top
  fl_color(label_color);
  fl_font(FL_COURIER, font_size);  // Default fallback

  int tw = 0, th = 0;
  fl_measure(label_text.c_str(), tw, th);
  fl_draw(label_text.c_str(), x() + (w() - tw)/2, y() + h() + 20);
  // Label near bottom
}
