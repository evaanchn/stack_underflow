// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "StartScene.hpp"
#include "GameOverScene.hpp"

#define MAIN_WINDOW_WIDTH 1920
#define MAIN_WINDOW_HEIGHT 1080
#define GAME_NAME "Vessels of Order: Battle for the Seas"
#define LOOP true

class App {
 public:
  App();
  int run();

 private:
  bool appActive;
  bool gameActive;
  SceneState currentState;

  sf::RenderWindow mainWindow;

  StartScene startScene;
  GameOverScene gameOverScene;

  SFMLSound startSceneMusic;
  SFMLSound gameOverSceneMusic;

 private:
  void setMainWindow();
  void runMainWindow();
  void handleGlobalEvents(sf::RenderWindow& window, sf::Event& event);
  void handleStateEvents(sf::Event& event);
  void handleStateRendering();

 private:
  void renderStartScene();
  void renderGameOverScene();
};
