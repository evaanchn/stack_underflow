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

#include "GameSceneConstants.hpp"

#include "GameInfoWindow.hpp"
#include "GameInfoText.hpp"
#include "LayeredButton.hpp"
#include "TextButton.hpp"


class GameScene {
 private:
  bool gameActive = ACTIVE;
  Fl_Window* window = nullptr;
  GameInfoWindow* infoWindow = nullptr;

  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr;

 private:
  int selectedAction = PROBE;
  TextButton* probeButton = nullptr, *exploreButton = nullptr
      , * attackButton = nullptr;
  std::vector<TextButton*> actionButtons = {};

 private:
  int selectedVessel = NONE_SELECTED;
  LayeredButton *bfsButton = nullptr, *dfsButton = nullptr
      , *dijkstraButton = nullptr, *floydButton = nullptr
      , *greedySearchButton = nullptr, *localSearchButton = nullptr
      , *exhausativeSearchButton = nullptr
      , *exhaustivePruneButton = nullptr;
  std::vector<std::vector<LayeredButton*>> vesselButtons = {};

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
  LayeredButton* createVesselButton(int x, int y
      , const std::string& imageName, int vesselID, bool hidden = true);
  void setVesselButtonAppearance(LayeredButton* button, std::string path);
  void setVesselButtonCallBack(LayeredButton* button, int vesselID);

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
