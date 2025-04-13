// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_Box.H>

class GameInfoText : public Fl_Box {
public:
  GameInfoText(int x, int y, int w, int h, const char* initialText
      , Fl_Color color);

  void updateText(const char* newText);
};
