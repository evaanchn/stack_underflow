// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameInfoText.hpp"

GameInfoText::GameInfoText(int x, int y, int w, int h
    , const char* initialText, Fl_Color color)
  : Fl_Box(x, y, w, h, initialText) {
  labelsize(30);
  labelfont(FL_COURIER);
  labelcolor(color);
  box(FL_NO_BOX);
}

void GameInfoText::updateText(const char* newText) {
  copy_label(newText);
  redraw();
}
