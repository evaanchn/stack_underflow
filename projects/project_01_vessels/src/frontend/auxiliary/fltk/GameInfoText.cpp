// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameInfoText.hpp"

GameInfoText::GameInfoText(int x, int y, int w, int h
    , const char* initialText, Fl_Color color)
  : Fl_Box(x, y, w, h, nullptr), currentText(nullptr) {
  currentText = new char[strlen(initialText) + 1];
  strcpy(currentText, initialText);
  label(currentText);

  labelsize(30);
  labelfont(FL_COURIER);
  labelcolor(color);
  box(FL_NO_BOX);
  }
  
  GameInfoText::~GameInfoText() {
    delete[] currentText;
  }
  
void GameInfoText::updateText(const char* newText) {
  delete[] currentText;
  currentText = new char[strlen(newText) + 1];
  strcpy(currentText, newText);
  label(currentText);
  redraw();
}
