// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title) {
  this->window = new Fl_Window(width, height, title.c_str());
  this->setBackground();
  // TODO add game elements
  this->window->end();  // Ends window's elements' grouping
  this->window->show();
}

GameScene::~GameScene() {
  delete this->backgroundImage;
  delete this->backgroundImageBox;
  delete this->window;
}

void GameScene::setBackground() {
  // Set game background
  this->backgroundImage = new Fl_PNG_Image(GAME_SCENE_BACKGROUND.c_str());
  // Position at corner, fill up window
  this->backgroundImageBox = new Fl_Box(/*X*/ 0, /*Y*/ 0, window->w()
      , window->h());
  this->backgroundImageBox->image(backgroundImage);  // Place image in box
  this->backgroundImageBox->box(FL_NO_BOX);  // No borders
  this->backgroundImageBox->redraw();  // Marks as needs a draw()
}

int GameScene::run() {
  while (this->gameActive) {
    this->handleEvents();
    this->update();
    // TODO (any) uncomment when game is included
    if (/*this->game->isGameOver()||*/ !this->window->visible()) {
      this->window->hide();
      this->gameActive = !ACTIVE;
    }
    Fl::check();  // Process events
    Fl::wait(0.02);  // Add a small delay to prevent CPU overuse
  }
  return Fl::run();
}

void GameScene::handleEvents() {

}

void GameScene::update() {

}