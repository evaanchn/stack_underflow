// Copyright 2025 stack_underflow CC-BY 4.0

#include "TextButton.hpp"

TextButton::TextButton(int x, int y, int w, int h, const char* label)
  : Fl_Button(x, y, w, h, label) {
  box(FL_FLAT_BOX);
  clear_visible_focus();
  labelsize(20);
  labelfont(FL_COURIER_BOLD);
  color(original_bg_color);
  labelcolor(original_text_color);
  callback(callbackThunk, this);
}

void TextButton::set_click_callback(std::function<void()> func) {
  this->onClick = func;
}

void TextButton::select() {
  color(selected_bg_color);
  labelcolor(selected_text_color);
  redraw();
}

void TextButton::deselect() {
  color(original_bg_color);
  labelcolor(original_text_color);
  redraw();
}

void TextButton::handleCallback() {
  if (onClick) {
    onClick();
  }
}

void TextButton::callbackThunk(Fl_Widget* widget, void* data) {
  if (auto* self = static_cast<TextButton*>(data)) {
    self->handleCallback();
  }
}
