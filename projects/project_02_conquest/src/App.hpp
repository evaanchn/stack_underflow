// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once


#include <iostream>

#include "StartScene.hpp"
#include "InformationScene.hpp"
#include "GameScene.hpp"

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720
#define GAME_WINDOW_WIDTH 1280
#define GAME_WINDOW_HEIGHT 720
#define GAME_NAME "CosmoConquest: Algorithms master"
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
  GameScene* gameScene = nullptr;

  SFMLSound startSceneMusic;
  SFMLSound informationSceneMusic;
  SFMLSound gameSceneMusic;
  SFMLSound gameOverSceneMusic;

  SFMLSound buttonClickSound;

 private:
  void setMainWindow();
  void runMainWindow();
  void handleGlobalEvents(sf::RenderWindow& window, sf::Event& event);
  void handleStateEvents(sf::Event& event);
  void handleStateRendering();

 private:
  void renderStartScene();
  void renderInformationScene();
  // void renderGameOverScene();

  int startGame();
  void endGame();
};
