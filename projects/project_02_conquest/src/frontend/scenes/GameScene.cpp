// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title) {
  this->window = new Fl_Window(width, height, title.c_str());
  this->setBackground();
  this->setLabels();
  this->setActionButtons();
  // TODO add game elements
  this->window->end();  // Ends window's elements' grouping
  this->window->show();
}

GameScene::~GameScene() {
  for (std::vector<CustomIconButton*>& row : this->vesselButtons) {
    for (CustomIconButton* vesselButton : row) {
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
  if (this->selectedAction != NO_ACTION) {
    this->actionButtons[this->selectedAction]->deselect();
  }

  if (this->vesselButtons.size() > 0) {
    // Deselect the other buttons, hide the other categories' vessel buttons
    for (CustomIconButton* vesselButton
        : this->vesselButtons[this->selectedAction]) {
      vesselButton->hide();
      vesselButton->deactivate();
    }
    for (CustomIconButton* vesselButton : this->vesselButtons[newAction]) {
      vesselButton->activate();
      vesselButton->show();
    }
  }
}

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

void GameScene::handleEvents() {

}

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