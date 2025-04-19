// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "ScenesConstants.hpp"

#include "SFMLSound.hpp"

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Window.H>

#include <vector>

#include "CustomIconButton.hpp"
#include "GameInfoText.hpp"
#include "GameInfoWindow.hpp"

#include "UIBoard.hpp"
#include "Game.hpp"

const Fl_Color GAME_BACKGROUND = fl_rgb_color(5, 10, 48);
const Fl_Color VESSELS_BACKGROUND = fl_rgb_color(143, 209, 230);

const std::string VESSELS_INFO[VESSELS_COUNT] =
    { "Lightning\nAlgorithm: Hashset\nHealth: 50\nAvg damage: 100\nWeight: 5"
    , "Ragnalog\nAlgorithm: Red-Black Tree\nHealth: 80\nAvg damage: 25\nWeight: 3"
    , "Wales\nAlgorithm: Binary Search\nHealth: 100\nAvg damage: 20\nWeight: 2"
    , "Thunder\nAlgorithm: BTree\nHealth: 120\nAvg damage: 16\nWeight: 2"
    , "Ratatosk\nAlgorithm: Splay Tree\nHealth: 150\nAvg damage: 10\nWeight: 2"
    , "Harbinger\nAlgorithm: Linear Search\nHealth: 200\nAvg damage: 2\nWeight: 1"
    };

class GameScene {
 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

  int run(); // Call this from a loop elsewhere

 private:
  bool gameActive;
  Fl_Window* window = nullptr;
  GameInfoWindow* infoWindow = nullptr;

 private:
  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr;

  Fl_Box* turnSwitchImageBox = nullptr;
  Fl_PNG_Image *switchToPlayer1Image = nullptr, *swithToPlayer2Image = nullptr;
  Fl_Input* inputSwitchPlayer = nullptr;
  std::string latestAction;

 private:
  CustomIconButton *buyButton = nullptr, *attackButton  = nullptr
      , *upgradeButton  = nullptr, *moveButton  = nullptr;
  CustomIconButton *hashsetButton = nullptr, *redBlackButton = nullptr
      , *bTreeButton = nullptr, *splayButton = nullptr
      , *binarySearchButton = nullptr, *linearSearchButton = nullptr;
  CustomIconButton *flagButton = nullptr, *unflagButton = nullptr;
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
  Fl_PNG_Image* vesselImagesRight[VESSELS_COUNT] = { nullptr, nullptr, nullptr
      , nullptr, nullptr, nullptr };
  Fl_PNG_Image* vesselImagesLeft[VESSELS_COUNT] = { nullptr, nullptr, nullptr
      , nullptr, nullptr, nullptr };

  CustomIconButton *exitButton;

  int selectedVessel;
  int selectedAction;

  MoveState moveState;
  Coordinates moveFrom;

 private:
  SFMLSound hitSound, missSound, boughtSound, movedSound
      , upgradedSound, actionButtonSound, vesselButtonSound;

 private:
  void setupUI();  // UI layout and element creation
  void setGameSceneBackground();
  void setTurnSwitchImages();
  void setActionButtons();
  void setVesselButtons();
  void setLabels();
  void setVesselImages();
  void setExitButton();

  void setActionButtonCallBack(CustomIconButton* button, int data);
  void setVesselButtonCallBack(CustomIconButton* button, int data);

  void handleEvents();
  void buyVessel();
  void attackVessel();
  void moveVessel();
  void upgradeVessel();
  void flagSlot();
  void unflagSlot();
  void handleExit();
  void concludeAction();

  void update();
  void updateLabels();
  void updateVesselWeightLabel();
  void updateCurrentPlayerLabel();
  void updateActionsLabel();
  void updateDrachmasLabel();
  void updateAmbrosiaPointsLabel();

  void showVesselInfo(int vesselID);
  void showSelectedVesselInfo();

  static void inputCallbackStatic(Fl_Widget* w, void* userData);
  void onInputCommand(Fl_Widget* w);
  void showSwitchTurnImage();

  void deactivateActionButtons();
  void activateActionButtons();

 private:
  UIBoard* board = nullptr;
  Game* game = nullptr;
};
