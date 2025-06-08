// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/fl_draw.H>
#include <memory>
#include <utility>

#include "UIPlanet.hpp"

class UIPath : public Fl_Widget {
 private:
  UIPlanet* planetA;
  UIPlanet* planetB;
  bool visible;
  size_t weight;
  Fl_Color color;

 public:
  UIPath(UIPlanet* a, UIPlanet* b, size_t weight = 0, Fl_Color color = FL_WHITE);
  
  void draw() override;
  void setVisible();
  void setWeight(size_t newWeight);
  void setColor(Fl_Color newColor);
  
  bool isVisible() const;
  int getWeight() const;
  std::pair<UIPlanet*, UIPlanet*> getPlanets() const;
};