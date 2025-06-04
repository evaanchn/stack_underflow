// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <string>
#include <vector>

#include "CustomIconButton.hpp"
#include "GameInfoText.hpp"
#include "TextButton.hpp"

#define ACTIVE true

const std::string SCENES_BACKGROUND_PATH = "assets/scenes_backgrounds/";
const std::string GAME_SCENE_BACKGROUND = SCENES_BACKGROUND_PATH
    + "gameScene.png";

const std::string VESSELS_SPRITES_PATH = "assets/sprites/spaceVessel/";
const std::vector<std::vector<std::string>> VESSEL_BUTTONS
    = {{"BFS.png", "DFS.png"}
    , {"Dijkstra.png", "Floyd.png"}
    , {"Greedy.png", "LocalSearch.png"
    , "Exhaustive.png", "ExhaustivePlus.png"}};

enum Actions {
  NO_ACTION = -1, PROBE, EXPLORE, ATTACK
};

struct ActionCallbackData {
  int* selectedAction;
  int actionID;
};

#define ACTION_BUTTONS_X 60
#define ACTION_BUTTON_W 150
#define ACTION_BUTTON_H 50

enum Vessels {
  NONE_SELECTED = -1, BFS, DFS, DIJKSTRA, FLOYD, GREEDY, LOCAL_SEARCH
  , EXHAUSTIVE, EXHAUSTIVE_PRUNED
};

#define LABELS_X 70
#define LONG_LABEL_BOX_W 300
#define LABEL_BOX_W 100
#define LABEL_BOX_H 70

class GameScene {
 private:
  bool gameActive;
  Fl_Window* window = nullptr;

  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr;

 private:
  int selectedAction = NO_ACTION;
  TextButton* probeButton = nullptr, *exploreButton = nullptr
      , * attackButton = nullptr;
  std::vector<TextButton*> actionButtons = {probeButton, exploreButton
      , attackButton};

 private:
  Vessels selectedVessel = NONE_SELECTED;
  std::vector<std::vector<CustomIconButton*>> vesselButtons;

  GameInfoText *remainingBossesLabel = nullptr, *ownedMinesLabel = nullptr
      , *availableEtheriumLabel = nullptr, *solarSystemsLeftLabel = nullptr;
  std::vector<GameInfoText*> labels = {remainingBossesLabel, ownedMinesLabel
      , availableEtheriumLabel, solarSystemsLeftLabel};
  // Group solar system so it can be removed without deleting previous elements
  Fl_Group* solarSystemArea = nullptr;

 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

 private:
  void setBackground();
  void setActionButtons();
  void setActionButtonCallBack(TextButton* button, int actionID);
  void setLabels();

  void switchVesselButtons(int newAction);
  void addSolarSystem();
  void removeSolarSystem();
  void refreshGameWindow();

 public:
  int run();

 private:
  void handleEvents();
  void update();

 private:
  void updateLabels();
  void updateRemainingBossesLabel();
  void updateOwnedMinesLabel();
  void updateAvailableEtheriumLabel();
  void updateSolarSystemsLeftLabel();
};
