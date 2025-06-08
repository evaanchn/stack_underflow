// Copyright 2025 stack_underflow CC-BY 4.0

#include "UIPath.hpp"

UIPath::UIPath(UIPlanet* a, UIPlanet* b, size_t weight, Fl_Color color)
    : Fl_Widget(0, 0, 1, 1)
    , planetA(a), planetB(b), weight(weight), color(color) {
  hide();
}

void UIPath::draw() {
  if (!planetA || !planetB) return;

  // Get center coordinates of both planets
  int x1 = planetA->getX() + planetA->getSize() / 2;
  int y1 = planetA->getY() + planetA->getSize() / 2;
  int x2 = planetB->getX() + planetB->getSize() / 2;
  int y2 = planetB->getY() + planetB->getSize() / 2;

  fl_color(color);
  fl_line_style(FL_SOLID, planetA->getSize() / 14);
  fl_line(x1, y1, x2, y2);

  // Draw weight label
  if (weight != 0) {
      int midX = (x1 + x2) / 2;
      int midY = (y1 + y2) / 2;
      std::string weightStr = std::to_string(weight);
      fl_color(FL_WHITE);
      fl_draw(weightStr.c_str(), midX, midY);
  }
}

void UIPath::reveal() {
  show();
  redraw();
}

void UIPath::setWeight(size_t newWeight) { weight = newWeight; redraw();}
void UIPath::setColor(Fl_Color newColor) { color = newColor; redraw();}

int UIPath::getWeight() const { return weight; }
std::pair<UIPlanet*, UIPlanet*> UIPath::getPlanets() const {
  return {planetA, planetB};
}
