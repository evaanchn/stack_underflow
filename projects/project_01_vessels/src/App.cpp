// Copyright 2025 stack_underflow CC-BY 4.0

#include "App.hpp"

App::App()
  : appActive(true)
  , gameActive(false)
  , currentState(GAME_OVER)
  , startScene()
  , gameOverScene()
  , startSceneMusic(MUSIC_FOLDER + "startScene.mp3", LOOP)
  , gameOverSceneMusic(MUSIC_FOLDER + "gameOverScene.wav", LOOP)
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
  else if (currentState == GAME_OVER) gameOverScene.handleEvent(mainWindow, event
    , currentState, appActive);
}

void App::handleStateRendering() {
  if (this->currentState == START) renderStartScene();
  else if (this->currentState == GAME_OVER) renderGameOverScene();
}

void App::renderStartScene() {
  gameOverSceneMusic.pause();
  startSceneMusic.play();
  startScene.draw(mainWindow);
}

void App::renderGameOverScene() {
  startSceneMusic.pause();  // TEMPORAL
  gameOverSceneMusic.play();
  gameOverScene.draw(mainWindow);
}
