// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title)
    : gameActive(ACTIVE)
    , actionButtonSound(SOUND_ACTION_BUTTON_PATH, false)
    , vesselButtonSound(VESSEL_BUTTON_SOUND_PATH, false) 
    , attackSound(SOUND_ATTACK_PATH, false)
    , newSystemSound(SOUND_NEW_SYSTEM_PATH, false) {
  this->window = new Fl_Window(width, height, title.c_str());
  this->setGameInstance();
  this->setBackground();
  this->setLabels();
  this->setActionButtons();
  this->setVesselButtons();
  this->setSolarSystemArea();
  this->window->end();  // Ends window's elements' grouping
  this->window->show();

  this->infoWindow = new GameInfoWindow();
}

GameScene::~GameScene() {
  delete this->infoWindow;
  delete this->solarSystem;
  delete this->solarSystemArea;
  for (std::vector<LayeredButton*>& row : this->vesselButtons) {
    for (LayeredButton* vesselButton : row) {
      if (vesselButton) delete vesselButton;
    }
  }
  for (TextButton* actionButton : this->actionButtons) delete actionButton;
  for (GameInfoText* label : this->labels) if (label) delete label;
  delete this->backgroundImage;
  delete this->backgroundImageBox;
  delete this->game;  // Delete game controller
  this->game = nullptr;  // Avoid dangling pointer
  delete this->window;
}


void GameScene::setGameInstance() {
  this->game = new Game();  // Initialize game controller
  if (!this->game) {
    throw std::runtime_error("Game instance could not be created");
  }
  if (!this->game->startGame()) {  // Start game with default galaxy file
    delete this->game;  // Delete game controller if it could not be started
    this->game = nullptr;  // Avoid dangling pointer
    throw std::runtime_error("Game could not be started");
  }
  if (this->game->getBattleLog()->setBattleLog(RECORD_GAME) == EXIT_FAILURE) {
    throw std::runtime_error("Battle log could not be set");
  }
}

void GameScene::setSolarSystemArea() {
  if (this->solarSystem) {
    delete this->solarSystem;
    this->solarSystem = nullptr;
  }
  if (this->solarSystemArea) {
    this->window->remove(this->solarSystemArea);
    delete this->solarSystemArea;
    this->solarSystemArea = nullptr;
  }
  this->solarSystemArea = new Fl_Group(RIGHT_HALF_START_X, 0
      , this->window->w() - RIGHT_HALF_START_X, this->window->h());
  this->solarSystemArea->box(FL_NO_BOX);  // no border
  this->solarSystem = new UISolarSystem();
  this->solarSystem->createPlanets(this->game->getCurrentPlanets());
  this->solarSystem->createPaths(this->game->getCurrentGraph()
    , this->solarSystemArea);
  // end of grouping
  this->solarSystemArea->end();
  // ensure group is added befor redraw
  this->window->add(this->solarSystemArea);
  this->window->redraw();
}

void GameScene::setBackground() {
  // Set game background
  this->backgroundImage = new Fl_PNG_Image(GAME_SCENE_BACKGROUND.c_str());
  // Position at corner, fill up window
  this->backgroundImageBox = new Fl_Box(/*X*/ 0, /*Y*/ 0, window->w()
      , window->h());
  this->backgroundImageBox->image(backgroundImage);  // Place image in box
  this->backgroundImageBox->box(FL_NO_BOX);  // No borders
  this->backgroundImageBox->redraw();  // Marks as needs a draw()
}

// TODO (any) leave initial texts as empty once game is implemented
void GameScene::setLabels() {
  this->remainingBossesLabel = new GameInfoText(110, /*Y*/ 20, LABEL_BOX_W
    , LABEL_BOX_H, "", FL_WHITE);
  this->ownedMinesLabel = new GameInfoText(90, /*Y*/ 100, LABEL_BOX_W
    , LABEL_BOX_H, "", FL_WHITE);
  this->availableEtheriumLabel = new GameInfoText(120, /*Y*/ 180, LABEL_BOX_W
    , LABEL_BOX_H, "", FL_WHITE);
  this->currentSystemLabel = new GameInfoText(40, /*Y*/ 560, LONG_LABEL_BOX_W
    , LABEL_BOX_H, "", FL_WHITE);
  this->solarSystemsLeftLabel = new GameInfoText(40, /*Y*/ 620, LONG_LABEL_BOX_W
    , LABEL_BOX_H, "", FL_WHITE);
  this->updateLabels();
}

void GameScene::setActionButtons() {
  this->probeButton = new TextButton(ACTION_BUTTONS_X, /*Y*/ 300
    , ACTION_BUTTON_W, ACTION_BUTTON_H, "PROBE");
  this->setActionButtonCallBack(this->probeButton, PROBE);

  this->scoutButton  = new TextButton(ACTION_BUTTONS_X, /*Y*/ 350
    , ACTION_BUTTON_W, ACTION_BUTTON_H, "SCOUT");
  this->setActionButtonCallBack(this->scoutButton, SCOUT);

  this->attackButton  = new TextButton(ACTION_BUTTONS_X, /*Y*/ 400
    , ACTION_BUTTON_W, ACTION_BUTTON_H, "ATTACK");
  this->setActionButtonCallBack(this->attackButton, ATTACK);

  actionButtons = {probeButton, scoutButton, attackButton};
}

void GameScene::setActionButtonCallBack(TextButton* button, int actionID) {
  button->set_click_callback([button, this, actionID]() {
    if (this->selectedVessel != NONE_SELECTED) {
      this->infoWindow->log(ALREADY_SELECTED(this->selectedVessel));
      return;  // Do not change action if a vessel is selected
    }
    if (this->selectedAction == BLOCKED) return;
    this->switchVesselButtons(actionID);
    this->selectedAction = actionID;
    this->actionButtonSound.play();
    button->select();
  });
}

void GameScene::switchVesselButtons(int newAction) {
  // Avoid switch if selected remains the same, or if NONE_SELECTED
  if (this->selectedAction == newAction
      || this->selectedAction == NONE_SELECTED
      || newAction == NONE_SELECTED) return;

  if (this->selectedAction != BLOCKED) {
    this->actionButtons[this->selectedAction]->deselect();
    // Hide and deactivate current selected actions' vessels
    for (LayeredButton* vesselButton
        : this->vesselButtons[this->selectedAction]) {
      if (vesselButton) {
        vesselButton->hide();
        vesselButton->deactivate();
        vesselButton->redraw();
      }
    }
  }

  if (newAction != BLOCKED) {
    // Activate and show new action's vessels
    for (LayeredButton* vesselButton : this->vesselButtons[newAction]) {
      if (vesselButton) {
        vesselButton->activate();
        vesselButton->show();
        vesselButton->redraw();
      }
    }
  }
}

#include "VesselsCollection.hpp"  // Include for constants
void GameScene::setVesselButtons() {
  // Initially visible buttons
  this->bfsButton = createVesselButton(VESSEL_X_LEFT, VESSEL_Y_MID
      , "BFS.png", VESSELS_LABELS[BFS_VESSEL], BFS_VESSEL, !VESSEL_HIDDEN);
  this->dfsButton = createVesselButton(VESSEL_X_RIGHT, VESSEL_Y_MID
      , "DFS.png", VESSELS_LABELS[DFS_VESSEL], DFS_VESSEL, !VESSEL_HIDDEN);

  // Hidden by default
  this->dijkstraButton = createVesselButton(VESSEL_X_LEFT, VESSEL_Y_MID
      , "Dijkstra.png", VESSELS_LABELS[DIJKSTRA_VESSEL], DIJKSTRA_VESSEL);
  this->floydButton = createVesselButton(VESSEL_X_RIGHT, VESSEL_Y_MID
      , "Floyd.png", VESSELS_LABELS[FLOYD_VESSEL], FLOYD_VESSEL);
  this->greedySearchButton = createVesselButton(VESSEL_X_LEFT, VESSEL_Y_TOP
      , "Greedy.png", VESSELS_LABELS[GREEDY_VESSEL], GREEDY_VESSEL);
  this->localSearchButton = createVesselButton(VESSEL_X_RIGHT, VESSEL_Y_TOP
      , "LocalSearch.png", VESSELS_LABELS[LOCAL_SEARCH_VESSEL]
      , LOCAL_SEARCH_VESSEL);
  this->exhausativeSearchButton = createVesselButton(VESSEL_X_LEFT
      , VESSEL_Y_BOTTOM, "Exhaustive.png"
      , VESSELS_LABELS[EXHAUSTIVE_SEARCH_VESSEL], EXHAUSTIVE_SEARCH_VESSEL);
  this->exhaustivePruneButton = createVesselButton(VESSEL_X_RIGHT
      , VESSEL_Y_BOTTOM, "ExhaustivePlus.png"
      , VESSELS_LABELS[EXHAUSTIVE_PRUNE_VESSEL], EXHAUSTIVE_PRUNE_VESSEL);

  this->vesselButtons = {
    {this->bfsButton, this->dfsButton}
    , {this->dijkstraButton, this->floydButton}
    , {this->greedySearchButton, this->localSearchButton
    , this->exhausativeSearchButton, this->exhaustivePruneButton}
  };
}

LayeredButton* GameScene::createVesselButton(int x, int y,
    const std::string& imageName, const std::string& label, int vesselID
    , bool hidden) {
  auto* button = new LayeredButton(x, y, VESSEL_BUTTON_DIM
      , VESSEL_BUTTON_DIM, label.c_str());
  this->setVesselButtonAppearance(button, VESSELS_SPRITES_PATH + imageName);
  this->setVesselButtonCallBack(button, vesselID);
  if (hidden) {
    button->hide();
    button->deactivate();
  }
  return button;
}

void GameScene::setVesselButtonAppearance(LayeredButton* button
    ,std::string path) {
  Fl_PNG_Image appearance = Fl_PNG_Image(path.c_str());
  button->setLayer(/*FIRST LAYER*/ 0, &appearance);
}

void GameScene::setVesselButtonCallBack(LayeredButton* button
    , int vesselID) {
  button->setOnClick([this, vesselID]() {
    // if (this->selectedAction == BLOCKED) return;
    if (this->selectedVessel == NONE_SELECTED) {
      this->selectedVessel = vesselID;
      this->vesselButtonSound.play();
    } else {
      this->infoWindow->log(ALREADY_SELECTED(this->selectedVessel));
    }
  });
}

int GameScene::run() {
  while (this->gameActive) {
    this->handleEvents();
    this->update();
    if (this->game->isGameOver() || !this->window->visible()) {
      this->window->hide();
      this->gameActive = !ACTIVE;
    }
    Fl::check();  // Process events
    Fl::wait(0.02);  // Add a small delay to prevent CPU overuse
  }
  return Fl::run();
}

void GameScene::handleEvents() {
  // Handle events for actions
  if (this->selectedAction == PROBE) {
    handleProbeAction();
  } else if (this->selectedAction == SCOUT) {
    handleScoutAction();
  } else if (this->selectedAction == ATTACK) {
    handleAttackAction();
  }
  if (this->selectedVessel == NONE_SELECTED) {
    this->handlePlanetSeek();
  }
  this->handleEtheriumProduction();
}

void GameScene::handleProbeAction() {
  if (this->selectedVessel != NONE_SELECTED) {
    int selectedPlanet = this->solarSystem->obtainSelectedPlanet();
    if (selectedPlanet != NONE_SELECTED) {
      if(!this->game->probe(this->selectedVessel, selectedPlanet)) {
        this->infoWindow->log("Failed, insuficient etherium\n"
          + VESSELS_DATA[selectedVessel]);
      }
      this->selectedVessel = NONE_SELECTED;  // Reset selected vessel
    }
  }
}

void GameScene::handleScoutAction() {
  if (this->selectedVessel != NONE_SELECTED) {
    int selectedPlanet = this->solarSystem->obtainSelectedPlanet();
    if (selectedPlanet != NONE_SELECTED) {
      if(!this->game->scout(this->selectedVessel, selectedPlanet)) {
        this->infoWindow->log("Failed, insuficient etherium\n"
          + VESSELS_DATA[selectedVessel]);
      }
      this->selectedVessel = NONE_SELECTED;  // Reset selected vessel
    }
  }
}
void GameScene::handleAttackAction() {
  if (this->selectedVessel != NONE_SELECTED) {
    int selectedPlanet = this->solarSystem->obtainSelectedPlanet();
    if (selectedPlanet != NONE_SELECTED) {
      int damage = this->game->attack(this->selectedVessel, selectedPlanet);
      if (damage == INSUFICIENT_ETHERIUM) {
        this->infoWindow->log("Failed, insuficient etherium\n"
          + VESSELS_DATA[selectedVessel]);
      } else if (damage == HAS_NO_BOSS){
        this->infoWindow->log("Failed, no boss at planet");
      } else {
        this->infoWindow->log(std::to_string(damage) + " damage pts");
        this->attackSound.play();

        // TODO prettify
        if(!this->game->getCurrentPlanets()[selectedPlanet]->hasBoss()) {
          this->solarSystem->removeBoss(selectedPlanet);
        }
      }
      this->selectedVessel = NONE_SELECTED;  // Reset selected vessel
    }
  }
}

void GameScene::handlePlanetSeek() {
  int selectedPlanet = this->solarSystem->obtainSelectedPlanet();
  if (selectedPlanet != NONE_SELECTED) {
    this->infoWindow->log(this->game->getCurrentPlanets().
      at(selectedPlanet)->toString());
  }
}

void GameScene::handleEtheriumProduction() {
  // Do not produce etherium if not enough time has passed
  if (this->etheriumClock.getElapsedTime().asSeconds()
      < ETHERUM_PRODUCTION_TIME) {
    return;
  }
  this->etheriumClock.restart();  // Restart the clock for next production
  this->game->collectEtherium();  // Collect etherium based on owned mines
  this->updateAvailableEtheriumLabel();
}

void GameScene::update() {
  if (this->selectedAction  == PROBE) {
    this->updateProbe();
  } else if (this->selectedAction == SCOUT) {
    this->updateScout();
  } else if (this->selectedAction == ATTACK) {
    this->updateAttack();
  }
  if (this->game->isCurrentSolarSystemCompleted()) {
    this->updateCompleteSystem();  // Update to next solar system
  }
}

void GameScene::updateProbe() {
  this->updateAvailableEtheriumLabel();
  this->solarSystem->updatePlanetsVisibility(this->game->getCurrentExplored()
    , this->game->getCurrentPlanets());
}

void GameScene::updateScout() {
  this->updateAvailableEtheriumLabel();
  this->solarSystem->updatePathsVisibility(this->game->getCurrentPaths());
  this->solarSystem->updatePlanetsVisibility(this->game->getCurrentExplored()
    , this->game->getCurrentPlanets());
}

void GameScene::updateAttack() {
  this->updateRemainingBossesLabel();
  this->updateOwnedMinesLabel();
  this->updateAvailableEtheriumLabel();
}

void GameScene::updateCompleteSystem() {
  // wait for confirmation before proceeding
  this->switchVesselButtons(BLOCKED);
  this->selectedAction = BLOCKED;  // don´t allow to handle actions
  std::string systemName = this->game->getGalaxy()->getCurrentSolarSystem()
    ->getName();
  this->infoWindow->solicitConfirmation(systemName + " completed");
  // update next
  if (this->infoWindow->getConfirmationChoice() == CONFIRM) {
    this->infoWindow->toggle();
    this->infoWindow->resetConfirmationChoice();
    this->updateNewSolarSystem();
  }
  this->updateLabels();
}

void GameScene::updateNewSolarSystem() {
  this->switchVesselButtons(PROBE);
  this->selectedAction = PROBE;
  // EndGame condition will stop run method
  if (this->game->passNextSolarSystem() == false) return;
  this->newSystemSound.play();
  this->newSystemSound.setVolume(100);
  this->updateCurrentSystemLabel();
  // this uiSolarSystemArea->hide();  // Hide old solar system area
  this->setSolarSystemArea();
}

void GameScene::updateLabels() {
  this->updateRemainingBossesLabel();
  this->updateOwnedMinesLabel();
  this->updateAvailableEtheriumLabel();
  this->updateCurrentSystemLabel();
  this->updateSolarSystemsLeftLabel();
}

void GameScene::updateRemainingBossesLabel() {
  std::string bosses = std::to_string(this->game->getCurrentRemainingBosses())
    + " remaining";
  this->remainingBossesLabel->updateText(bosses.c_str());
  this->remainingBossesLabel->hide();  // Hide to force redraw
  this->remainingBossesLabel->show();  // Show again to update the label
  this->remainingBossesLabel->redraw();  // Redraw to update the label
}

void GameScene::updateOwnedMinesLabel() {
  std::string minesOWned = std::to_string(this->game->getCurrentMInes())
    + " owned";
  this->ownedMinesLabel->updateText(minesOWned.c_str());
  this->ownedMinesLabel->hide();  // Hide to force redraw
  this->ownedMinesLabel->show();  // Show again to update the label
  this->ownedMinesLabel->redraw();  // Redraw to update the label
}

void GameScene::updateAvailableEtheriumLabel() {
  std::string etherium = std::to_string(this->game->getCurrentEtherium())
    + " available";
  this->availableEtheriumLabel->updateText(etherium.c_str());
  this->availableEtheriumLabel->hide();  // Hide to force redraw
  this->availableEtheriumLabel->show();  // Show again to update the label
  this->availableEtheriumLabel->redraw();  // Redraw to update the label
}

void GameScene::updateCurrentSystemLabel() {
  std::string systemName = this->game->getGalaxy()->getCurrentSolarSystem()
    ->getName();
  this->currentSystemLabel->updateText(systemName.c_str());
}

void GameScene::updateSolarSystemsLeftLabel() {
  std::string solarSystemsLeft = 
      std::to_string(this->game->getSystemsLeftCount()) + " solar systems left";
  this->solarSystemsLeftLabel->updateText(solarSystemsLeft.c_str());
}
