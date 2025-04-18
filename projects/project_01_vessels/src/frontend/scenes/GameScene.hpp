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

#include <iostream>  // TODO (5n4v3) delete

const Fl_Color GAME_BACKGROUND = fl_rgb_color(5, 10, 48);
const Fl_Color VESSELS_BACKGROUND = fl_rgb_color(143, 209, 230);

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

  void setActionButtonCallBack(CustomIconButton* button, int data);
  void setVesselButtonCallBack(CustomIconButton* button, int data);

  void update();

  void handleActionButtonsEvents();
  void buyVessel();
  void attackVessel();
  void moveVessel();
  void upgradeVessel();
  void flagSlot();
  void unflagSlot();
  void handleExit();
  

  void updateLabels();

  static void inputCallbackStatic(Fl_Widget* w, void* userData);
  void onInputCommand(Fl_Widget* w);
  void showSwitchTurnImage();

  void deactivateActionButtons();
  void activateActionButtons();

 private:
  UIBoard* board = nullptr;
};
