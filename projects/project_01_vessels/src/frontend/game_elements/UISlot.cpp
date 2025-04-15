// Copyright 2025 stack_underflow CC-BY 4.0

#include "UISlot.hpp"

// Constructor initialization
UISlot::UISlot(int x, int y) {
  button = new Fl_Button(x, y, SLOT_DIMENSION, SLOT_DIMENSION);
  button->box(FL_FLAT_BOX);
  // Tells slot's button that it will execute onClick when clicked
  button->callback([](Fl_Widget* widget, void* data) {
    if (widget) {
      auto* self = static_cast<UISlot*>(data);
      if (self->onClick) {
        self->onClick();
      }
    }
  }, this);
}

// Destructor cleanup
UISlot::~UISlot() {
  delete button;
}

// Method to set the callback
void UISlot::setOnClick(std::function<void()> func) {
  this->onClick = func;
}

// Method to deactivate the button
void UISlot::deactivate() {
  button->deactivate();
}

// Method to set button color
void UISlot::setColor(Fl_Color color) {
  button->color(color);
}

// Method to set vessel image
void UISlot::setVessel(Fl_PNG_Image* _vessel) {
  if (_vessel) {
    vessel = _vessel;
    button->image(vessel);
    button->redraw();
  }
}

Fl_PNG_Image* UISlot::getVessel() {
  return this->vessel;
}

// Method to clear vessel image
void UISlot::clearVessel() {
  vessel = nullptr;
  button->image(nullptr);
  button->redraw();
}
