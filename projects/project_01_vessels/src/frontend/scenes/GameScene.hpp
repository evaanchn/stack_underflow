// Copyright 2025 stack_underflow CC-BY 4.0
// TODO (E): FIX GAME WINDOW CLOSE PROBLEM
#pragma once

#include "ScenesConstants.hpp"

#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>

#include <vector>

#include "CustomIconButton.hpp"
#include "GameInfoText.hpp"

#include <iostream>  // TODO delete

#define ACTION_BUTTON_DIM 100
#define VESSEL_BUTTON_DIM 100

#define A_BUTTONS_COUNT 4
#define V_BUTTONS_COUNT 6
#define GAME_LABELS_COUNT 5

#define ACTION_BUTTONS_X 1750
#define VESSELS_BUTTON_Y 820

#define LABEL_BOX_W 50
#define LABEL_BOX_H 18

enum ACTIONS { UPGRADE, MOVE, ATTACK, BUY};
enum VESSELS { LINEAR_SEARCH, SPLAY_TREE, BINARY_SEARCH, BTREE, RB_TREE, SET };

class GameScene {
 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

  int run(); // Call this from a loop elsewhere

 private:
  bool gameActive;
  Fl_Window* window;
  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr; 


  CustomIconButton *buyButton = nullptr, *attackButton  = nullptr
      , *upgradeButton  = nullptr, *moveButton  = nullptr;
  CustomIconButton *hashsetButton = nullptr, *redBlackButton = nullptr
      , *bTreeButton = nullptr, *splayButton = nullptr
      , *binarySearchButton = nullptr, *linearSearchButton = nullptr;
  GameInfoText *vesselsWeight = nullptr, *currentPlayerLabel = nullptr
      , *actionsLabel = nullptr, *drachmas = nullptr, *ambrosiaPoints = nullptr;

  CustomIconButton* actionsButtons[A_BUTTONS_COUNT] =
      { moveButton, upgradeButton, attackButton, buyButton };
  CustomIconButton* vesselsButtons[V_BUTTONS_COUNT] =
      { linearSearchButton, splayButton, binarySearchButton, bTreeButton
      , redBlackButton, hashsetButton };
  GameInfoText* gameLabels[GAME_LABELS_COUNT] =
      { ambrosiaPoints, drachmas, actionsLabel, currentPlayerLabel
      , vesselsWeight };

  CustomIconButton *exitButton;

  int selectedVessel;
  int selectedAction;

 private:
  void setupUI();  // UI layout and element creation
  void setGameSceneBackground();
  void setActionButtons();
  void setVesselButtons();
  void setLabels();

  void setActionButtonCallBack(CustomIconButton* button, int data);
  void setVesselButtonCallBack(CustomIconButton* button, int data);
};
