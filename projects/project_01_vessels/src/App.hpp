// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "StartScene.hpp"
#include "InformationScene.hpp"
#include "GameScene.hpp"
#include "GameOverScene.hpp"

#include <iostream>

#define MAIN_WINDOW_WIDTH 1920
#define MAIN_WINDOW_HEIGHT 1080
#define GAME_WINDOW_WIDTH 1920
#define GAME_WINDOW_HEIGHT 1080
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
  InformationScene informationScene;
  GameScene* gameScene;
  GameOverScene gameOverScene;

  SFMLSound startSceneMusic;
  SFMLSound gameSceneMusic;
  SFMLSound gameOverSceneMusic;

 private:
  void setMainWindow();
  void runMainWindow();
  void handleGlobalEvents(sf::RenderWindow& window, sf::Event& event);
  void handleStateEvents(sf::Event& event);
  void handleStateRendering();

 private:
  void renderStartScene();
  void renderInformationScene();
  void renderGameOverScene();

  int startGame();
  void endGame();
};
