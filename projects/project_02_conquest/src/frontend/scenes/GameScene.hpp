// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "SFMLSound.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <string>
#include <vector>

#include "GameSceneConstants.hpp"
#include "UISolarSystem.hpp"

#include "GameInfoWindow.hpp"
#include "GameInfoText.hpp"
#include "LayeredButton.hpp"
#include "TextButton.hpp"

#include "Game.hpp"  // Include controller

class GameScene {
 private:
  bool gameActive = ACTIVE;
  Fl_Window* window = nullptr;
  GameInfoWindow* infoWindow = nullptr;

  Fl_Box* backgroundImageBox = nullptr;
  Fl_PNG_Image* backgroundImage = nullptr;

 private:
  int selectedAction = PROBE;
  TextButton* probeButton = nullptr, *scoutButton = nullptr
      , * attackButton = nullptr;
  std::vector<TextButton*> actionButtons = {};
  SFMLSound actionButtonSound;

 private:
  int selectedVessel = NONE_SELECTED;
  LayeredButton *bfsButton = nullptr, *dfsButton = nullptr
      , *dijkstraButton = nullptr, *floydButton = nullptr
      , *greedySearchButton = nullptr, *localSearchButton = nullptr
      , *exhausativeSearchButton = nullptr
      , *exhaustivePruneButton = nullptr;
  std::vector<std::vector<LayeredButton*>> vesselButtons = {};
  SFMLSound vesselButtonSound;
  SFMLSound attackSound;

 private:
  GameInfoText *remainingBossesLabel = nullptr, *ownedMinesLabel = nullptr
      , *availableEtheriumLabel = nullptr, *currentSystemLabel = nullptr
      , *solarSystemsLeftLabel = nullptr;
  std::vector<GameInfoText*> labels = {remainingBossesLabel, ownedMinesLabel
      , availableEtheriumLabel, currentSystemLabel, solarSystemsLeftLabel};

 private:
  Game* game = nullptr;  // Controller for the game logic
  sf::Clock etheriumClock;  // Clock to manage etherium production timing

  // TODO (ANY) add solarSystemArea implementation
  // Group solar system so it can be removed without deleting previous elements
  // with delete UiSolarSystem and then this->window->remove(solarSystemArea)
  // then add another and add to the group and restart the group
  Fl_Group* solarSystemArea = nullptr;
  UISolarSystem* solarSystem = nullptr;

  SFMLSound newSystemSound;

 public:
  GameScene(int width, int height, const std::string& title);
  ~GameScene();

 private:
  void setGameInstance();
  void setSolarSystemArea();

  void setBackground();
  void setLabels();
  void setActionButtons();
  void setActionButtonCallBack(TextButton* button, int actionID);
  void switchVesselButtons(int newAction);
  
  void setVesselButtons();
  LayeredButton* createVesselButton(int x, int y
      , const std::string& imageName, const std::string& label, int vesselID
      , bool hidden = true);
  void setVesselButtonAppearance(LayeredButton* button, std::string path);
  void setVesselButtonCallBack(LayeredButton* button, int vesselID);


 public:
  int run();

 private:
  void handleEvents();
  void handleProbeAction();
  void handleScoutAction();
  void handleAttackAction();
  void handlePlanetSeek();
  void handleEtheriumProduction();

 private:
  void update();

  void updateProbe();
  void updateScout();
  void updateAttack();

  void updateCompleteSystem();
  void updateNewSolarSystem();

  void updateLabels();
  void updateRemainingBossesLabel();
  void updateOwnedMinesLabel();
  void updateAvailableEtheriumLabel();
  void updateCurrentSystemLabel();
  void updateSolarSystemsLeftLabel();
};
