// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title)
    : gameActive(ACTIVE) {
  this->window = new Fl_Window(width, height, title.c_str());
  this->setBackground();
  this->setLabels();
  this->setActionButtons();
  this->setVesselButtons();
  // TODO add game elements
  this->window->end();  // Ends window's elements' grouping
  this->window->show();

  this->infoWindow = new GameInfoWindow();
}

GameScene::~GameScene() {
  for (std::vector<LayeredButton*>& row : this->vesselButtons) {
    for (LayeredButton* vesselButton : row) {
      if (vesselButton) delete vesselButton;
    }
  }
  for (TextButton* actionButton : this->actionButtons) delete actionButton;
  for (GameInfoText* label : this->labels) if (label) delete label;
  delete this->backgroundImage;
  delete this->backgroundImageBox;
  delete this->window;
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
      , LABEL_BOX_H, "1 remaining", FL_WHITE);
  this->ownedMinesLabel = new GameInfoText(90, /*Y*/ 100, LABEL_BOX_W
      , LABEL_BOX_H, "1 owned", FL_WHITE);
  this->availableEtheriumLabel = new GameInfoText(120, /*Y*/ 180, LABEL_BOX_W
      , LABEL_BOX_H, "999 available", FL_WHITE);
  this->solarSystemsLeftLabel = new GameInfoText(40, /*Y*/ 620, LONG_LABEL_BOX_W
      , LABEL_BOX_H, "9 solar systems left", FL_WHITE);
}

void GameScene::setActionButtons() {
  this->probeButton = new TextButton(ACTION_BUTTONS_X, /*Y*/ 300
      , ACTION_BUTTON_W, ACTION_BUTTON_H, "PROBE");
  this->setActionButtonCallBack(this->probeButton, PROBE);

  this->exploreButton  = new TextButton(ACTION_BUTTONS_X, /*Y*/ 350
      , ACTION_BUTTON_W, ACTION_BUTTON_H, "EXPLORE");
  this->setActionButtonCallBack(this->exploreButton, EXPLORE);

  this->attackButton  = new TextButton(ACTION_BUTTONS_X, /*Y*/ 400
      , ACTION_BUTTON_W, ACTION_BUTTON_H, "ATTACK");
  this->setActionButtonCallBack(this->attackButton, ATTACK);

  actionButtons = {probeButton, exploreButton, attackButton};
}

void GameScene::setActionButtonCallBack(TextButton* button, int actionID) {
  button->set_click_callback([button, this, actionID]() {
    this->switchVesselButtons(actionID);
    this->selectedAction = actionID;
    button->select();
  });
}

void GameScene::switchVesselButtons(int newAction) {
  // Avoid switch if selected remains the same, or if NONE_SELECTED is involved
  if (this->selectedAction == newAction
      || this->selectedAction == NONE_SELECTED
      || newAction == NONE_SELECTED) return;

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
  // Activate and show new action's vessels
  for (LayeredButton* vesselButton : this->vesselButtons[newAction]) {
    if (vesselButton) {
      vesselButton->activate();
      vesselButton->show();
      vesselButton->redraw();
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
    if (this->selectedVessel == NONE_SELECTED) {
      this->selectedVessel = vesselID;
      this->infoWindow->log(VESSELS_DATA[vesselID]);
      // TODO(any): add vessel button sound
      // this->vesselButtonSound.play();
    }
  });
}

int GameScene::run() {
  while (this->gameActive) {
    this->handleEvents();
    this->update();
    // TODO (any) uncomment when game is included
    if (/*this->game->isGameOver()||*/ !this->window->visible()) {
      this->window->hide();
      this->gameActive = !ACTIVE;
    }
    Fl::check();  // Process events
    Fl::wait(0.02);  // Add a small delay to prevent CPU overuse
  }
  return Fl::run();
}

// TODO (ANY) add handle methdods for each available action (3)
void GameScene::handleEvents() {

}

// TODO (ANY) complete update method, depending on game occurences
void GameScene::update() {

}

// TODO (any) uncomment once game is implemented
void GameScene::updateLabels() {
  this->updateRemainingBossesLabel();
  this->updateOwnedMinesLabel();
  this->updateAvailableEtheriumLabel();
  this->updateSolarSystemsLeftLabel();
}

void GameScene::updateRemainingBossesLabel() {
  // std::string bosses = std::to_string(this->game->getCurrentRemainingBosses())
  //     + " remaining"
  // this->remainingBossesLabel->updateText(bosses.c_str());
}

void GameScene::updateOwnedMinesLabel() {
  // std::string minesOWned = std::to_string(this->game->getCurrentOwnedMines())
  //     + " owned";
  // this->ownedMinesLabel->updateText(minesOWned.c_str());
}

void GameScene::updateAvailableEtheriumLabel() {
  // std::string etherium = std::to_string(this->game->getCurrentEtherium())
  //     + "available";
  // this->availableEtheriumLabel->updateText(etherium.c_str());
}

void GameScene::updateSolarSystemsLeftLabel() {
  // std::string solarSystemsLeft = 
  //     std::to_string(this->game->getSolarSystemsLeft());
  // this->solarSystemLeftLabel->updateText(solarSystemsLeft.c_str());
}
