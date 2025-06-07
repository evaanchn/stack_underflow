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

#include "GameInfoText.hpp"
#include "LayeredButton.hpp"
#include "TextButton.hpp"
#include "UISolarSystem.hpp"

#define ACTIVE true

const std::string SCENES_BACKGROUND_PATH = "assets/scenes_backgrounds/";
const std::string GAME_SCENE_BACKGROUND = SCENES_BACKGROUND_PATH
    + "gameScene.png";


enum ACTIONS {
  NO_ACTION = -1, PROBE, EXPLORE, ATTACK
};

#define ACTION_BUTTONS_X 60
#define ACTION_BUTTON_W 150
#define ACTION_BUTTON_H 50

enum VESSEL_ID {
  BFS, DFS, DIJKSTRA, FLOYD, GREEDY, LOCAL_SEARCH
  , EXHAUSTIVE, EXHAUSTIVE_PRUNED
};

#define LABELS_X 70
#define LONG_LABEL_BOX_W 300
#define LABEL_BOX_W 100
#define LABEL_BOX_H 70

#define VESSEL_BUTTON_DIM 100
const std::string VESSELS_SPRITES_PATH = "assets/sprites/spaceVessel/";

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
  size_t selectedVessel = NONE_SELECTED;
  LayeredButton *bfsButton = nullptr, *dfsButton = nullptr
      , *dijkstraButton = nullptr, *floydButton = nullptr
      , *greedySearchButton = nullptr, *localSearchButton = nullptr
      , *exhausativeSearchButton = nullptr
      , *exhaustivePruneButton = nullptr;
  std::vector<std::vector<LayeredButton*>> vesselButtons
      = {{bfsButton, dfsButton}
      , {dijkstraButton, floydButton}
      , {greedySearchButton, localSearchButton
      , exhausativeSearchButton, exhaustivePruneButton}};

 private:
  GameInfoText *remainingBossesLabel = nullptr, *ownedMinesLabel = nullptr
      , *availableEtheriumLabel = nullptr, *solarSystemsLeftLabel = nullptr;
  std::vector<GameInfoText*> labels = {remainingBossesLabel, ownedMinesLabel
      , availableEtheriumLabel, solarSystemsLeftLabel};

  // TODO (ANY) add solarSystemArea implementation
  // Group solar system so it can be removed without deleting previous elements
  // with delete UiSolarSystem and then this->window->remove(solarSystemArea)
  // then add another and add to the group and restart the group
  Fl_Group* solarSystemArea = nullptr;
  UISolarSystem* solarSystem = nullptr;

 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

 private:
  void setBackground();
  void setLabels();
  void setActionButtons();
  void setActionButtonCallBack(TextButton* button, int actionID);
  void switchVesselButtons(int newAction);

  void setVesselButtons();
  void setVesselButtonCallBack(LayeredButton* button, size_t vesselID);

  void setSolarSystem(std::vector<Planet*> planets);
  void testPlanetLoading(); // Test method

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
