// Copyright 2025 stack_underflow CC-BY 4.0

#include "LayeredButton.hpp"
#include <FL/fl_draw.H>

LayeredButton::LayeredButton(int x, int y, int w, int h)
    : Fl_Button(x, y, w, h) {
  box(FL_NO_BOX);
  label(nullptr);
  clear_visible_focus();  // Removes focus rectangle
  box(FL_FLAT_BOX);
  // Tells button that it will execute onClick when clicked
  callback([](Fl_Widget* widget, void* data) {
    if (widget) {
      auto* self = static_cast<LayeredButton*>(data);
      if (self->onClick) {
        self->onClick();
      }
    }
  }, this);
}

LayeredButton::~LayeredButton() {
  this->clearAllLayers();
}

void LayeredButton::setLayer(size_t index, Fl_Image* image) {
  if (index >= this->layers.size()) {
    this->layers.resize(index + 1, nullptr);
  }

  // Scale image to fit inside button
  double scaleX = static_cast<double>(this->w()) / image->w();
  double scaleY = static_cast<double>(this->h()) / image->h();
  double scale = std::min(scaleX, scaleY);

  int newW = static_cast<int>(image->w() * scale);
  int newH = static_cast<int>(image->h() * scale);

  // Store a copy of the image, scaled, to layer
  if (!this->layers[index]) this->layers[index] = image->copy(newW, newH);
  redraw();
}

void LayeredButton::clearLayer(size_t index) {
  if (index < this->layers.size()) {
    delete this->layers[index];
    this->layers[index] = nullptr;
    redraw();
  }
}

void LayeredButton::clearAllLayers() {
  for (auto* layer : this->layers) {
    if (layer) delete layer;
  }
  this->layers.clear();
  redraw();
}

void LayeredButton::draw() {
  // Ensuresit doesn't draw beyond set region inside the button
  fl_push_clip(x(), y(), w(), h());
  // Draw all layers
  for (auto* img : this->layers) {
    if (img) img->draw(x(), y(), w(), h());  // Draw scaled to button size
  }
  fl_pop_clip();
}

// Method to set the callback
void LayeredButton::setOnClick(std::function<void()> func) {
  this->onClick = func;
}
