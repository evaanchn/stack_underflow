// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <string>
#include <functional>

enum Confirmation { NO_CHOICE, CONFIRM, CANCEL };

#define INFO_WINDOW_WIDTH 300
#define INFO_WINDOW_HEIGHT 170

#define CONFIRM_BUTTONS_WIDTH 100
#define CONFIRM_BUTTONS_HEIGHT 30
#define CONFIRM_BUTTONS_SPACING 20

class GameInfoWindow {
 public:
  explicit GameInfoWindow(int width = INFO_WINDOW_WIDTH
      , int height = INFO_WINDOW_HEIGHT, const char* title = "Game Info");
  ~GameInfoWindow();

  void show();
  void hide();
  void toggle();
  void log(const std::string& message);
  void solicitConfirmation(const std::string& message);
  void resetConfirmationChoice();
  Confirmation getConfirmationChoice();
  void clear();

 private:
  Fl_Window* window;
  Fl_Text_Display* display;
  Fl_Text_Buffer* buffer;
  Fl_Button* confirmButton;
  Fl_Button* cancelButton;

  Confirmation confirmationInput;
};
