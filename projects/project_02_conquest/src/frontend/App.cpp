// Copyright 2025 stack_underflow CC-BY 4.0

#include "App.hpp"

App::App()
  : appActive(true)
  , gameActive(false)
  , currentState(SceneState::START)
  , startScene()
  // , informationScene()
  // , gameOverScene()
  , startSceneMusic(MUSIC_FOLDER + "startScene.wav", LOOP)
  , informationSceneMusic(MUSIC_FOLDER + "informationScene.wav", LOOP)
  , gameSceneMusic(MUSIC_FOLDER + "gameScene.wav", LOOP, /*Volume*/ 60)
  , gameOverSceneMusic(MUSIC_FOLDER + "gameOverScene.wav", LOOP, /*Volume*/ 120)
  , buttonClickSound(SOUNDS_FOLDER + "soundButtonClick.wav", !LOOP, /*Vol*/ 200)
  {
  setMainWindow();
}

void App::setMainWindow() {
}

int App::run() {
}

void App::runMainWindow() {
}

void App::handleGlobalEvents(sf::RenderWindow& window, sf::Event& event) {
}

void App::handleStateEvents(sf::Event& event) {
}

void App::handleStateRendering() {
}

void App::renderStartScene() {
}

void App::renderInformationScene() {
}

void App::renderGameOverScene() {
}

int App::startGame() {
}

void App::endGame() {
}
