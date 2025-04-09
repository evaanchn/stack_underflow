// Copyright 2025 stack_underflow CC-BY 4.0

#include "App.hpp"

App::App()
  : appActive(true)
  , gameActive(false)
  , currentState(START)
  , startScene(), startSceneMusic(MUSIC_FOLDER + "startScene.mp3", true)
  {
  setMainWindow();
}

void App::setMainWindow() {
  if (!mainWindow.isOpen()) {
    mainWindow.create(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)
        , GAME_NAME);
  }
}


int App::run() {
  while (this->appActive) {
    if (!this->gameActive) {
      runMainWindow();
    } else {
      // FLTK Game menu
    }
  }
  return EXIT_SUCCESS;
}

void App::runMainWindow() {
  while (mainWindow.isOpen()) {
      sf::Event event;
      while (mainWindow.pollEvent(event)) {
          handleGlobalEvents(mainWindow, event);
          handleStateEvents(event);
      }

      mainWindow.clear();
      handleStateRendering();
      mainWindow.display();
  }
}

void App::handleGlobalEvents(sf::RenderWindow& window, sf::Event& event) {
  if (event.type == sf::Event::Closed) {
      window.close();
      appActive = false;
  }
}

void App::handleStateEvents(sf::Event& event) {
  if (currentState == START) startScene.handleEvent(mainWindow, event
      , currentState);
  
}

void App::handleStateRendering() {
  if (this->currentState == START) renderStartScene();
}

void App::renderStartScene() {
  startSceneMusic.play();
  startScene.draw(mainWindow);
}