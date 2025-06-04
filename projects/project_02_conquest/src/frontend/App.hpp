// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "StartScene.hpp"
#include "InformationScene.hpp"

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720
#define GAME_NAME "Space Ops: Algorithms Conquest"
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
  SFMLSound startSceneMusic;

 private:
  void setMainWindow();
  void runMainWindow();
  void handleGlobalEvents(sf::RenderWindow& window, sf::Event& event);
  void handleStateEvents(sf::Event& event);
  void handleStateRendering();

 private:
  void renderStartScene();
};