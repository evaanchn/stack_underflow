// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <functional>
#include <string>

class CustomIconButton : public Fl_Button {
 public:
  CustomIconButton(int x, int y, int w, int h
    , const std::string& icon_path, const std::string& text
    , Fl_Color color);
  ~CustomIconButton() { delete icon; }

  void setLabelText(const std::string& text) { label_text = text; redraw(); }
  void setFontSize(int size) { font_size = size; redraw(); }
  void setLabelColor(Fl_Color color) { label_color = color; redraw(); }
  void setFontFace(const std::string& face) { font_face = face; redraw(); }

  // Set a callback function
  // USAGE: my_btn->set_click_callback([&obj]() {
  // obj.method();
  //});
  void set_click_callback(std::function<void()> func) { clickCallback = func; }

  // Virtual on_click method that can be overridden
  virtual void on_click() {
    // Default does nothing; override if desired 
  }

  void draw() override;

 private:
  Fl_PNG_Image* icon;
  std::string label_text;
  int font_size;
  Fl_Color label_color;
  std::string font_face;
  std::function<void()> clickCallback;

  // FLTK static callback wrapper
  static void StaticCallback(Fl_Widget* w, void* data) {
    if (w) {
      CustomIconButton* btn = static_cast<CustomIconButton*>(data);
      if (btn) {
        btn->on_click(); // Call virtual method
        if (btn->clickCallback) {
          btn->clickCallback(); // Call custom callback if set
        }
      }
    }
  }
};
