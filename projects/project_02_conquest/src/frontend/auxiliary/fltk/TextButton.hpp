// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_Button.H>
#include <functional>

class TextButton : public Fl_Button {
 public:
  TextButton(int x, int y, int w, int h, const char* label = "");
  ~TextButton() = default;

  void set_click_callback(std::function<void()> func);

  void select();    // Apply selected colors
  void deselect();  // Revert to default colors

 protected:
  void handleCallback();

 private:
  std::function<void()> onClick;

  Fl_Color original_text_color = FL_WHITE;
  Fl_Color original_bg_color = FL_BLACK;

  Fl_Color selected_text_color = FL_BLACK;
  Fl_Color selected_bg_color = FL_WHITE;

  static void callbackThunk(Fl_Widget* widget, void* data);
};
