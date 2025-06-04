// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <string>
#include <vector>

#include "AnimatedGIF.hpp"
#include "UIPlanet.hpp"

#define ACTIVE true

const std::string SCENES_BACKGROUND_PATH = "assets/scenes_backgrounds/";
const std::string GAME_SCENE_BACKGROUND = SCENES_BACKGROUND_PATH
    + "gameScene.png";

class GameScene {
 private:
  bool gameActive;
  Fl_Window* window = nullptr;

  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr;

  // Group solar system so it can be removed without deleting previous elements
  Fl_Group* solarSystemArea = nullptr;

 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

 private:
  void setBackground();
  void addSolarSystem();
  void removeSolarSystem();
  void refreshGameWindow();

 public:
  int run();

 private:
  void handleEvents();
  void update();
};
