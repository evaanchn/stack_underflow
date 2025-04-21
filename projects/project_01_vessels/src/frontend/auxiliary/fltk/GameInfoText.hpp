// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <cstring>

class GameInfoText : public Fl_Box {
 public:
  GameInfoText(int x, int y, int w, int h, const char* initialText
      , Fl_Color color);
  ~GameInfoText();

  void updateText(const char* newText);

 private:
  char* currentText = nullptr;
};
