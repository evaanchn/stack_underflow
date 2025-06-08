// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameInfoWindow.hpp"

GameInfoWindow::GameInfoWindow(int posX, int posY, int windowWidth
  , int windowHeight, const char* title) {
  window = new Fl_Window(posX, posY, windowWidth, windowHeight, title);
  this->window->color(FL_BLACK);
  this->window->labelcolor(FL_WHITE);

  // Total width of both buttons + spacing
  int buttonsTotalWidth = CONFIRM_BUTTONS_WIDTH * 2 + CONFIRM_BUTTONS_SPACING;

  // Center X for the group
  int buttonsX = (windowWidth - buttonsTotalWidth) / 2;
  // 20px margin from bottom
  int buttonsY = windowHeight - CONFIRM_BUTTONS_HEIGHT - 20;

  // Display box: smaller and centered
  int displayWidth = windowWidth - 40;
  int displayHeight = windowHeight - 35;
  int displayX = (windowWidth - displayWidth) / 2;
  int displayY = 20;

  display = new Fl_Text_Display(displayX, displayY, displayWidth
      , displayHeight);
  buffer = new Fl_Text_Buffer();
  display->buffer(buffer);
  display->textfont(FL_COURIER);

  // Confirm Button
  confirmButton = new Fl_Button(buttonsX, buttonsY, CONFIRM_BUTTONS_WIDTH,
      CONFIRM_BUTTONS_HEIGHT, "Confirm");
  confirmButton->labelcolor(FL_WHITE);
  confirmButton->labelfont(FL_COURIER);
  confirmButton->color(FL_DARK_GREEN); // Button background
  confirmButton->callback([](Fl_Widget*, void* data) {
      GameInfoWindow* self = static_cast<GameInfoWindow*>(data);
      self->confirmationInput = CONFIRM;
  }, this);

  // Cancel Button
  cancelButton = new Fl_Button(buttonsX + CONFIRM_BUTTONS_WIDTH
      + CONFIRM_BUTTONS_SPACING, buttonsY
      , CONFIRM_BUTTONS_WIDTH, CONFIRM_BUTTONS_HEIGHT, "Cancel");
  cancelButton->labelcolor(FL_WHITE);
  cancelButton->labelfont(FL_COURIER);
  cancelButton->color(FL_DARK_RED);
  cancelButton->callback([](Fl_Widget*, void* data) {
      GameInfoWindow* self = static_cast<GameInfoWindow*>(data);
      self->confirmationInput = CANCEL;
  }, this);


  window->end();
}

GameInfoWindow::~GameInfoWindow() {
  delete display;
  delete buffer;
  delete confirmButton;
  delete cancelButton;
  delete window;
}

void GameInfoWindow::show() { 
  window->show();
}

void GameInfoWindow::hide() { 
  window->hide();
}

void GameInfoWindow::toggle() { 
  window->visible() ? hide() : show();
}

void GameInfoWindow::log(const std::string& message) {
  buffer->text(message.c_str());
  confirmButton->hide();
  cancelButton->hide();
  window->redraw();
  window->show();
}

void GameInfoWindow::clear() {
  buffer->text("");
}

void GameInfoWindow::solicitConfirmation(const std::string& message) {
  this->buffer->text(message.c_str());
  this->confirmButton->show();
  this->cancelButton->show();
  this->window->redraw();
  this->confirmButton->activate();
  this->cancelButton->activate();
}

void GameInfoWindow::resetConfirmationChoice() {
  this->confirmationInput = NO_CHOICE;
  this->confirmButton->deactivate();
  this->cancelButton->deactivate();
  this->confirmButton->hide();
  this->cancelButton->hide();
}

Confirmation GameInfoWindow::getConfirmationChoice() {
  return this->confirmationInput;
}
