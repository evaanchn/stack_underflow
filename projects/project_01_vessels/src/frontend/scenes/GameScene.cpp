// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title)
  : gameActive (ACTIVE)
  , hitSound(SOUNDS_FOLDER + "hit.wav", /*loop*/ false)
  , missSound(SOUNDS_FOLDER + "miss.wav", /*loop*/ false)
  , boughtSound(SOUNDS_FOLDER + "boughtVessel.wav", /*loop*/ false)
  , movedSound(SOUNDS_FOLDER + "movedVessel.wav", /*loop*/ false)
  , upgradedSound(SOUNDS_FOLDER + "upgradedVessel.wav", /*loop*/ false)
  , actionButtonSound(SOUNDS_FOLDER + "soundActionButton.wav", /*loop*/ false)
  , vesselButtonSound(SOUNDS_FOLDER + "soundVesselButton.wav", /*loop*/ false)
  {
  this->selectedAction = NONE_SELECTED;
  this->selectedVessel = NONE_SELECTED;
  this->window = new Fl_Window(width, height, title.c_str());
  
  this->setupUI();
  this->board = new UIBoard();
  this->setTurnSwitchImages();  // Set turn switch cutscenes
  this->window->end();  // Ends window's elements' grouping
  this->window->show();

  this->game = new Game();
  
  this->infoWindow = new GameInfoWindow();
  this->moveState = MOVE_IDLE;
  this->latestAction = EMPTY_TEXT;
}

GameScene::~GameScene() {
  delete this->infoWindow;

  delete this->inputSwitchPlayer;
  delete this->turnSwitchImageBox;
  delete this->swithToPlayer2Image;
  delete this-> switchToPlayer1Image;

  delete this->board;
  delete this->game;

  delete this->exitButton;

  for (int i = VESSELS_COUNT - 1; i >= 0; --i) {
    if (this->vesselImagesLeft[i]) delete this->vesselImagesLeft[i];
    if (this->vesselImagesRight[i]) delete this->vesselImagesRight[i];
  }

  for (int i = 0; i < GAME_LABELS_COUNT; ++i) 
      if(gameLabels[i]) delete gameLabels[i];
  for (int i = 0; i < V_BUTTONS_COUNT; ++i)
      if(vesselsButtons[i]) delete vesselsButtons[i];

  delete this->unflagButton;
  delete this->flagButton;
  for (int i = 0; i < A_BUTTONS_COUNT; ++i)
      if(actionsButtons[i]) delete actionsButtons[i];

  delete this->backgroundImageBox;
  delete this->backgroundImage;
  delete this->window;
}

void GameScene::setupUI() {
  setGameSceneBackground();
  setActionButtons();
  setVesselButtons();
  setLabels();
  setVesselImages();
  setExitButton();
}

void GameScene::setGameSceneBackground() {
  // Set game background
  backgroundImage = new Fl_PNG_Image("assets/scenes_backgrounds/gameScene.png");
  // Position at corner, fill up window
  backgroundImageBox = new Fl_Box(/*X*/ 0, /*Y*/ 0, window->w(), window->h());
  backgroundImageBox->image(backgroundImage);  // Place image in box
  backgroundImageBox->box(FL_NO_BOX);  // No borders
  backgroundImageBox->redraw();  // Marks as needs a draw()
}

void GameScene::setTurnSwitchImages() {
  // Set turn switch images
  switchToPlayer1Image
      = new Fl_PNG_Image("assets/scenes_backgrounds/switchToPlayer1.png");
  swithToPlayer2Image
      = new Fl_PNG_Image("assets/scenes_backgrounds/switchToPlayer2.png");
  turnSwitchImageBox = new Fl_Box(/*X*/ 0, /*Y*/ 0, window->w(), window->h());
  turnSwitchImageBox->image(switchToPlayer1Image);  // Place image in box
  turnSwitchImageBox->box(FL_NO_BOX);  // No borders
  turnSwitchImageBox->redraw();  // Marks as needs a draw()

  inputSwitchPlayer = new Fl_Input(/*X*/ 1780, /*Y*/ 950, /*W*/ 120, /*H*/ 30
      , /*Label*/ "Type OK to continue:");
  inputSwitchPlayer->when(FL_WHEN_ENTER_KEY_ALWAYS); // Respond to Enter key
  inputSwitchPlayer->labelcolor(FL_WHITE);
  inputSwitchPlayer->labelfont(FL_COURIER_BOLD);
  inputSwitchPlayer->labelsize(20);
  inputSwitchPlayer->textfont(FL_COURIER);
  inputSwitchPlayer->textsize(20);
  inputSwitchPlayer->callback(inputCallbackStatic, this);
  inputSwitchPlayer->hide();  // Hide input field
  inputSwitchPlayer->deactivate();  // Deactivate input field
  inputSwitchPlayer->redraw();  // Marks as needs a draw()
}

void GameScene::setActionButtons() {
  buyButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 220
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "buyRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  setActionButtonCallBack(buyButton, BUY);

  attackButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 385
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "attackRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  setActionButtonCallBack(attackButton, ATTACK);

  moveButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 540
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "moveRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  setActionButtonCallBack(moveButton, MOVE);

  upgradeButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 700
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "upgradeRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  setActionButtonCallBack(upgradeButton, UPGRADE);

  flagButton = new CustomIconButton(/*X*/ 20, /*Y*/ 555
      , 50, 50
      , GAME_BUTTONS_FOLDER + "flag.png", "Flag", GAME_BACKGROUND);
  setActionButtonCallBack(flagButton, FLAG);

  unflagButton = new CustomIconButton(/*X*/ 20, /*Y*/ 645
      , 50, 50
      , GAME_BUTTONS_FOLDER + "unflag.png", "Unflag", GAME_BACKGROUND);
  setActionButtonCallBack(unflagButton, UNFLAG);
}

void GameScene::setActionButtonCallBack(CustomIconButton* button, int actionID) {
  button->set_click_callback([this, actionID]() { 
    if (this->selectedAction == NONE_SELECTED) {
      this->selectedAction = actionID;
      // Reset any previous selections, just in case
      this->selectedVessel = NONE_SELECTED;
      this->board->resetSelection(PLAYER_1);
      this->board->resetSelection(PLAYER_2);
      this->actionButtonSound.play();
    }
  });
}

void GameScene::setVesselButtons() {
  hashsetButton = new CustomIconButton(/*X*/ 1190, VESSELS_BUTTON_Y + 10
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "Set.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(hashsetButton, SET);

  redBlackButton = new CustomIconButton(/*X*/ 980, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "RedBlackTree.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(redBlackButton, RB_TREE);

  bTreeButton = new CustomIconButton(/*X*/ 765, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "BTree.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(bTreeButton, B_TREE);

  binarySearchButton = new CustomIconButton(/*X*/ 550, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "BinarySearch.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(binarySearchButton, BINARY_SEARCH);

  splayButton = new CustomIconButton(/*X*/ 355, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "SplayTree.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(splayButton, SPLAY_TREE);

  linearSearchButton = new CustomIconButton(/*X*/ 155, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_RIGHT_FOLDER + "LinearSearch.png", EMPTY_TEXT, VESSELS_BACKGROUND);
  setVesselButtonCallBack(linearSearchButton, LINEAR_SEARCH);
}

void GameScene::setVesselButtonCallBack(CustomIconButton* button, int data) {
  button->set_click_callback([this, data]() {
    this->selectedVessel = data;
    this->vesselButtonSound.play();
  });
}

void GameScene::setLabels() {
  vesselsWeight = new GameInfoText(/*X*/ 380, /*Y*/ 47, LABEL_BOX_W
      , LABEL_BOX_H, "", FL_WHITE);
  currentPlayerLabel = new GameInfoText(/*X*/ 1400, /*Y*/ 47, LONG_LABEL_BOX_W
      , LABEL_BOX_H, "", FL_WHITE);
  actionsLabel = new GameInfoText(/*X*/ 1745, /*Y*/ 160, LABEL_BOX_W
      , LABEL_BOX_H, "", FL_WHITE);
  drachmas = new GameInfoText(/*X*/ 1582, /*Y*/ 790, LABEL_BOX_W
      , LABEL_BOX_H, "", FL_BLACK);
  ambrosiaPoints = new GameInfoText(/*X*/ 1572, /*Y*/ 867, LABEL_BOX_W
      , LABEL_BOX_H, "", FL_BLACK);
}

void GameScene::setVesselImages() {
  for (int i = 0; i < VESSELS_COUNT; ++i) {
    std::string vesselFilePathRight = VESSELS_RIGHT_FOLDER + VESSEL_SPRITES[i];
    vesselImagesRight[i] = new Fl_PNG_Image(vesselFilePathRight.c_str());

    std::string vesselFilePathLeft = VESSELS_LEFT_FOLDER + VESSEL_SPRITES[i];
    vesselImagesLeft[i] = new Fl_PNG_Image(vesselFilePathLeft.c_str());
  }
}

void GameScene::setExitButton() {
  this->exitButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 855
    , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
    , GAME_BUTTONS_FOLDER + "exitRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  this->exitButton->set_click_callback([this]() {
    this->infoWindow->show();
    this->infoWindow->solicitConfirmation("\n\nConfirm exit");
    this->actionButtonSound.play();
    this->selectedAction = EXIT;
  });
}

// MAIN LOOP
int GameScene::run() {
  // Game logic and redraws can go here
  while (gameActive) {
    this->handleEvents();
    this->update();
    if (this->game->isGameOver() || !this->window->visible()) {
      this->window->hide();
      this->gameActive = !ACTIVE;
    }
    Fl::check();   // Process events
    Fl::wait(0.02); // Add a small delay to prevent CPU overuse
  }
  return Fl::run();
}

void GameScene::handleEvents() {
  if (this->selectedAction == BUY) this->buyVessel();
  else if (this->selectedAction == MOVE) this->moveVessel();
  else if (this->selectedAction == ATTACK) this->attackVessel();
  else if (this->selectedAction == UPGRADE) this->upgradeVessel();
  else if (this->selectedAction == FLAG) this->flagSlot();
  else if (this->selectedAction == UNFLAG) this->unflagSlot();
  else if (this->selectedAction == EXIT) this->handleExit();
  else {
    // Show vessel general info
    if (this->selectedVessel != NONE_SELECTED)
        this->showVesselInfo(this->selectedVessel);
    else this->showSelectedVesselInfo();  // Show selected vessel current info
  }
}

void GameScene::buyVessel() {
  if (this->game->getCurrentVesselWeight() == MAX_VESSEL_WEIGHT
      || this->game->getCurrentPurchasePoints() == 0) {
    this->infoWindow->log("Cannot buy more vessels");
    this->selectedAction = NONE_SELECTED;
    return;
  }

  if (this->selectedAction == BUY) {
    int currentPlayer = this->game->getCurrentPlayer();
    int buyingVessel = this->selectedVessel;
    // Inform user if the selected vessel is purchaseable
    if (buyingVessel == NONE_SELECTED) {
      this->infoWindow->log("Select a vessel to buy");
      return;
    } else {
      std::string canBuy = this->game->canBuyVessel(buyingVessel) ?
        "*PURCHASEABLE*" : "*INSUFFICIENT FUNDS*";
      this->infoWindow->log(VESSELS_INFO[buyingVessel] + "\n" + canBuy);
    }

    // Validate drachmas and weight
    if(this->game->canBuyVessel(buyingVessel)) {
      Coordinates* settingCoordinates
        = this->board->getCoordinates(currentPlayer);
      int row = settingCoordinates->row;
      int col = settingCoordinates->col;

      if (buyingVessel != NONE_SELECTED && row != NONE_SELECTED
          && col != NONE_SELECTED && !this->game->isSlotOccupied(row, col)) {
        // Set vessel in backend
        this->game->setVesselAt(row, col, buyingVessel);
        this->latestAction = "Successfully bought vessel!";
        Fl_PNG_Image* vesselImage = currentPlayer == PLAYER_1 ?
            vesselImagesRight[buyingVessel] : vesselImagesLeft[buyingVessel];
        this->board->setVesselAt(settingCoordinates->row
            , settingCoordinates->col, vesselImage);
        
        this->boughtSound.play();
        this->concludeAction();

        this->updateVesselWeightLabel();
      }
    } else {
      this->board->resetSelection(currentPlayer);
    }
  }
}

void GameScene::attackVessel() {
  if (this->selectedAction == ATTACK) {
    int currentPlayer = this->game->getCurrentPlayer();

    Coordinates* attackingVesselCoordinates
        = this->board->getCoordinates(currentPlayer);
    int attackerRow = attackingVesselCoordinates->row;
    int attackerCol = attackingVesselCoordinates->col;
    // Validate that there was a valid row selected
    if (attackerRow != NO_COORDINATES && attackerCol != NO_COORDINATES) {
      if (this->game->isSlotOccupied(attackerRow, attackerCol)) {
        Coordinates* attackedVesselCoordinates
          = this->board->getCoordinates((currentPlayer + 1) % 2);
        int victimRow = attackedVesselCoordinates->row;
        int victimCol = attackedVesselCoordinates->col;
        if (victimRow == NO_COORDINATES
            || victimCol == NO_COORDINATES) {
          this->infoWindow->log("Select a slot to attack");
          return;
        }

        bool victimVessel = this->game->isSlotOccupied(victimRow, victimCol);
        size_t calculatedDamage =
            this->game->attackVessel(attackerRow, attackerCol
            , victimRow, victimCol);
        if (this->game->isSlotOccupied(victimRow, victimCol)) {
          this->hitSound.play();
          this->latestAction= "Successfully attacked!\nDamage: " +
              std::to_string(calculatedDamage);
          this->board->setHitMaskAt(victimRow, victimCol);
        } else if (victimVessel &&
            !this->game->isSlotOccupied(victimRow, victimCol)) {
          // Means there was a vessel but not anymore
          this->hitSound.play();
          this->latestAction = "Successfully defeated an enemy vessel!";
          this->board->removeVesselAt(victimRow, victimCol);
          this->board->resetMaskAt(victimRow, victimCol, SHOW_RESET);
        } else {
          this->missSound.play();
          this->latestAction = "Missed!\nDamage: "
              + std::to_string(calculatedDamage) + "\nAmbrosia points granted";
        }
        this->concludeAction();
        this->updateAmbrosiaPointsLabel();
      }
    } else this->infoWindow->log("Select attacking vessel");
  }
}

void GameScene::moveVessel() {
  if (this->selectedAction == MOVE) {
    int currentPlayer = this->game->getCurrentPlayer();
    Coordinates* clicked = this->board->getCoordinates(currentPlayer);
    // Validate that there was an actual click
    if (clicked && clicked->row != NONE_SELECTED
        && clicked->col != NONE_SELECTED) {
      if (this->moveState == MOVE_IDLE) this->moveState = MOVE_SELECT_VESSEL;

      // Selecting a vessel stage, then selecting destination stage
      if (this->moveState == MOVE_SELECT_VESSEL) {
        if (this->game->isSlotOccupied(clicked->row, clicked->col)) {
          moveFrom = *clicked;
          this->board->resetSelection(currentPlayer);
          // Remove previous flags
          this->board->resetMaskAt(moveFrom.row, moveFrom.col, !SHOW_RESET);
          this->moveState = MOVE_SELECT_DESTINATION;
          this->infoWindow->log("Select a destination");
        }
      } else if (this->moveState == MOVE_SELECT_DESTINATION) {
        if (!this->game->isSlotOccupied(clicked->row, clicked->col)) {
          this->game->moveVessel(moveFrom.row, moveFrom.col
              , clicked->row, clicked->col);
          this->board->moveVessel(moveFrom.row, moveFrom.col
              , clicked->row, clicked->col);
          // Updates
          this->latestAction = "Successfully moved vessel!";
          this->movedSound.play(); 
          this->moveState = MOVE_IDLE;
          this->concludeAction();
        }
      }
    } else if (this->moveState == MOVE_IDLE)
        this->infoWindow->log("Select a vessel to move");
  }
}

void GameScene::upgradeVessel() {
  if (this->selectedAction == UPGRADE) {
    int currentPlayer = this->game->getCurrentPlayer();

    Coordinates* upgradingVesselCoordinates
        = this->board->getCoordinates(currentPlayer);
    int row = upgradingVesselCoordinates->row, 
        col = upgradingVesselCoordinates->col;
    // Validate that there was an actual click on a valid slot
    if (row != NO_COORDINATES && col != NO_COORDINATES) {
      if(this->game->isSlotOccupied(row, col)) {
        if (this->game->upgradeVessel(row, col)) {
          // Updates
          this->latestAction = "Successfully upgraded!\n";
          this->upgradedSound.play();
        } else {
          this->latestAction = "Could not upgrade vessel";
        }
        this->concludeAction();
        this->updateAmbrosiaPointsLabel();
      }
    } else this->infoWindow->log("Select a vessel to upgrade");
  }
}

void GameScene::concludeAction() {
  // Updates and resets that need to be done after every action
  this->selectedAction = NONE_SELECTED;
  this->selectedVessel = NONE_SELECTED;
  this->game->consumeAction();
  this->updateActionsLabel();
  this->updateDrachmasLabel();
  this->board->resetSelection(this->game->getCurrentPlayer());
  this->infoWindow->log(this->latestAction);

}

void GameScene::flagSlot() {
  if (this->selectedAction == FLAG) {
    int opponent = this->game->getOpponent();

    Coordinates* flaggingCoordinates
        = this->board->getCoordinates(opponent);
    int row = flaggingCoordinates->row;
    int col = flaggingCoordinates->col;
    if (row != NO_COORDINATES && col != NO_COORDINATES) {
      this->board->setFlaggedMaskAt(row, col);
      this->selectedAction = NONE_SELECTED;
    }
  }
}

void GameScene::unflagSlot () {
  if (this->selectedAction == UNFLAG) {
    int opponent = this->game->getOpponent();

    Coordinates* unflaggingCoordinates
        = this->board->getCoordinates(opponent);
    int row = unflaggingCoordinates->row;
    int col = unflaggingCoordinates->col;
    if (row != NO_COORDINATES && col != NO_COORDINATES) {
      this->board->resetMaskAt(row, col, SHOW_RESET);
      this->selectedAction = NONE_SELECTED;
    }
  }
}

void GameScene::handleExit() {
  if (this->selectedAction == EXIT) {
    if (this->infoWindow->getConfirmationChoice() == CONFIRM) {
      this->infoWindow->hide();
      this->window->hide();
    }
    else if (this->infoWindow->getConfirmationChoice() == CANCEL) {
      this->infoWindow->hide();
      this->infoWindow->resetConfirmationChoice();
      this->selectedAction = NONE_SELECTED;
    }
  }
}

void GameScene::update() {
  this->checkVesselWeight();

  // if game won, no need to update
  if (this->game->isGameOver()) {
    std::string winner = this->game->getWinner() == PLAYER_1 ?
        "Poseidon" : "Njord";
    this->infoWindow->log("\n\nGame Over!\n" + winner + " wins!");
  } else this->updateTurnSwitch();
}

void GameScene::checkVesselWeight() {
  if (this->game->getCurrentVesselWeight() == 0) {
    this->moveButton->deactivate();
    this->attackButton->deactivate();
    this->upgradeButton->deactivate();
  }
  else {
    this->moveButton->activate();
    this->attackButton->activate();
    this->upgradeButton->activate();
  }
}

void GameScene::updateTurnSwitch() {
  if (this->game->switchedTurns()) {
    this->infoWindow->show();
    this->infoWindow->solicitConfirmation(latestAction
        + "\n\nConfirm to proceed");
    
    if (this->infoWindow->getConfirmationChoice() == CONFIRM) {
      // To prevent any action while switching turns
      this->deactivateButtons();
      this->board->deactivateBoard();

      this->infoWindow->hide();
      this->infoWindow->resetConfirmationChoice();

      // Only activate input when confirmed
      this->inputSwitchPlayer->activate();
      this->inputSwitchPlayer->show();

      // Switch to a new turn
      this->game->setNewTurn();
      int currentPlayer = this->game->getCurrentPlayer();
      this->board->resetSelection(currentPlayer);
      this->board->maskOpponentSlots(currentPlayer);
      this->updateLabels();  // Update to new current player's data
      this->showSwitchTurnImage();
    }
  }
}

void GameScene::updateLabels() {
  this->updateVesselWeightLabel();
  this->updateCurrentPlayerLabel();
  this->updateActionsLabel();
  this->updateDrachmasLabel();
  this->updateAmbrosiaPointsLabel();
}

void GameScene::updateVesselWeightLabel() {
  std::string weightText = std::to_string(this->game->getCurrentVesselWeight())
       + "/10";
  this->vesselsWeight->updateText(weightText.c_str());
}

void GameScene::updateCurrentPlayerLabel() {
  std::string currentPlayerText = this->game->getCurrentPlayer() == PLAYER_1 ?
      "Poseidon's turn" : "Njord's turn";
  currentPlayerLabel->updateText(currentPlayerText.c_str());
}

void GameScene::updateActionsLabel() {
  std::string actionsText = std::to_string(this->game->getCurrentActionCount())
      + "/3";
  this->actionsLabel->updateText(actionsText.c_str());
}

void GameScene::updateDrachmasLabel() {
  std::string drachmasText = 
      std::to_string(this->game->getCurrentPurchasePoints());
  this->drachmas->updateText(drachmasText.c_str());
}

void GameScene::updateAmbrosiaPointsLabel() {
  std::string ambrosiaText = 
      std::to_string(this->game->getCurrentUpgradePoints());
  this->ambrosiaPoints->updateText(ambrosiaText.c_str());
}

void GameScene::showVesselInfo(int vesselID) {
  this->infoWindow->log(VESSELS_INFO[vesselID]);
}

void GameScene::showSelectedVesselInfo() {
  int currentPlayer = this->game->getCurrentPlayer();
  Coordinates* selectedVesselCoordinates
      = this->board->getCoordinates(currentPlayer);
  int row = selectedVesselCoordinates->row
      , col = selectedVesselCoordinates->col;
  if (this->selectedAction == NONE_SELECTED
      && row != NO_COORDINATES && col != NO_COORDINATES) {
    if (this->game->isSlotOccupied(row, col))
      this->infoWindow->log(this->game->getVesselInfoAt(row, col));
  }
}

// Static callback trampoline
void GameScene::inputCallbackStatic(Fl_Widget* w, void* userData) {
  GameScene* self = static_cast<GameScene*>(userData);
  self->onInputCommand(w);
}

// Actual callback handler
void GameScene::onInputCommand(Fl_Widget* w) {
  if (w) {
    const char* command = this->inputSwitchPlayer->value();
    if (strcmp(command, "ok") == 0 || strcmp(command, "OK") == 0) {
      if (turnSwitchImageBox) {
          turnSwitchImageBox->hide();
          this->inputSwitchPlayer->hide();
          this->activateButtons();
          this->board->activateBoard();
          this->window->cursor(FL_CURSOR_HAND);
          window->redraw();
      }
    }
  }

  // Clear input after handling
  this->inputSwitchPlayer->value("");
}

void GameScene::showSwitchTurnImage() {
  if (turnSwitchImageBox) {
    int currentPlayer = this->game->getCurrentPlayer();
    if (currentPlayer == PLAYER_1) {
      turnSwitchImageBox->image(switchToPlayer1Image);
    } else {
      turnSwitchImageBox->image(swithToPlayer2Image);
    }
    turnSwitchImageBox->show();
    window->redraw();
  }
}

void GameScene::deactivateButtons() {
  for (int i = 0; i < A_BUTTONS_COUNT; ++i) {
    if (actionsButtons[i]) actionsButtons[i]->deactivate();
  }
  for (int i = 0; i < V_BUTTONS_COUNT; ++i) {
    if (vesselsButtons[i]) vesselsButtons[i]->deactivate();
  }
  this->exitButton->deactivate();
}

void GameScene::activateButtons() {
  for (int i = 0; i < A_BUTTONS_COUNT; ++i) {
    if (actionsButtons[i]) actionsButtons[i]->activate();
  }
  for (int i = 0; i < V_BUTTONS_COUNT; ++i) {
    if (vesselsButtons[i]) vesselsButtons[i]->activate();
  }
  this->exitButton->activate();
}
