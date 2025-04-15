// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title)
  : gameActive (ACTIVE)
  , moveState (MOVE_IDLE) {
  this->selectedAction = NONE_SELECTED;
  this->selectedVessel = NONE_SELECTED;
  window = new Fl_Window(width, height, title.c_str());
  this->setupUI();
  this->board = new UIBoard();
  this->window->end();  // Ends window's elements' grouping
  this->window->show();
}

GameScene::~GameScene() {
  delete this->board;
  delete this->exitButton;

  for (int i = VESSELS_COUNT - 1; i >= 0; --i) {
    if (this->vesselImagesLeft[i]) delete this->vesselImagesLeft[i];
    if (this->vesselImagesRight[i]) delete this->vesselImagesRight[i];
  }

  for (int i = 0; i < GAME_LABELS_COUNT; ++i) 
      if(gameLabels[i]) delete gameLabels[i];
  for (int i = 0; i < V_BUTTONS_COUNT; ++i)
      if(vesselsButtons[i]) delete vesselsButtons[i];
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
  this->exitButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 855
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "exitRune.png", EMPTY_TEXT, GAME_BACKGROUND);
  this->exitButton->set_click_callback([this]() {
    this->window->hide();
  });
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
}

void GameScene::setActionButtonCallBack(CustomIconButton* button, int actionID) {
  button->set_click_callback([this, actionID]() { 
    if (this->selectedAction == NONE_SELECTED) {
      this->selectedAction = actionID;
      // Reset any previous selections, just in case
      this->selectedVessel = NONE_SELECTED;
      this->board->resetSelection(PLAYER_1);
      this->board->resetSelection(PLAYER_2);
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
  setVesselButtonCallBack(bTreeButton, BTREE);

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
  button->set_click_callback([this, data]() { this->selectedVessel = data; });
}

void GameScene::setLabels() {
  vesselsWeight = new GameInfoText(/*X*/ 410, /*Y*/ 73, LABEL_BOX_W
      , LABEL_BOX_H, "0/10", FL_WHITE);
  currentPlayerLabel = new GameInfoText(/*X*/ 1535, /*Y*/ 73, LABEL_BOX_W
      , LABEL_BOX_H, "Player 1's turn", FL_WHITE);
  actionsLabel = new GameInfoText(/*X*/ 1770, /*Y*/ 180, LABEL_BOX_W
      , LABEL_BOX_H, "3/3", FL_WHITE);
  drachmas = new GameInfoText(/*X*/ 1615, /*Y*/ 817, LABEL_BOX_W
      , LABEL_BOX_H, "10", FL_BLACK);
  ambrosiaPoints = new GameInfoText(/*X*/ 1605, /*Y*/ 893, LABEL_BOX_W
      , LABEL_BOX_H, "0", FL_BLACK);
}

void GameScene::setVesselImages() {
  for (int i = 0; i < VESSELS_COUNT; ++i) {
    std::string vesselFilePathRight = VESSELS_RIGHT_FOLDER + VESSEL_SPRITES[i];
    vesselImagesRight[i] = new Fl_PNG_Image(vesselFilePathRight.c_str());

    std::string vesselFilePathLeft = VESSELS_LEFT_FOLDER + VESSEL_SPRITES[i];
    vesselImagesLeft[i] = new Fl_PNG_Image(vesselFilePathLeft.c_str());
  }
}

int GameScene::run() {
  // Game logic and redraws can go here
  while (gameActive) {
    this->handleActionButtonsEvents();
    if (!this->window->visible()) { this->gameActive = !ACTIVE; }
    Fl::check();   // Process events
    Fl::wait(0.02); // Add a small delay to prevent CPU overuse
  }
  return Fl::run();
}

void GameScene::handleActionButtonsEvents() {
  if (this->selectedAction == BUY) this->buyVessel();
  else if (this->selectedAction == MOVE) this->moveVessel();
  else if (this->selectedAction == ATTACK) this->attackVessel();
  else if (this->selectedAction == UPGRADE) this->upgradeVessel();
}

void GameScene::buyVessel() {
  // MUST CHECK IF VESSEL WEIGHT FOR CURRENT PLAYER IS NOT MAX
  // this->game->validateVesselWeight();
  if (this->selectedAction == BUY) {
    // GET CURRENT PLAYER ID FROM GAME
    int currentPlayer = PLAYER_1; // this->game->getCurrentPlayer();
    int buyingVessel = this->selectedVessel; // NONE_SELECTED;
    // CHECK IF HAS ENOUGH MONEY TO BUY AND IF WEIGHT IS PERMITTED
    // this->game->canBuyVessel(vesselType);
    Coordinates* settingCoordinates
        = this->board->getCoordinates(currentPlayer);
    int row = settingCoordinates->row;
    int col = settingCoordinates->col;

    if (buyingVessel != NONE_SELECTED && row != NONE_SELECTED
      && col != NONE_SELECTED) {
      // CHECK IF COORDINATE IN BACKEND HAS SOMETHING. MUST BE FREE
      // this->game->isSlotOccupied(row, col);

      // IF NOT OCCUPIED
      // this->game->setVesselAt(row, col, buyingVessel);
      Fl_PNG_Image* vesselImage = currentPlayer == PLAYER_1 ?
          vesselImagesRight[buyingVessel] : vesselImagesLeft[buyingVessel];
      this->board->setVesselAt(settingCoordinates->row, settingCoordinates->col
          , vesselImage);
      this->selectedAction = NONE_SELECTED;
      // CONSUME ACTIONS
      // this->game->consumeAction();
    }
  }
}

void GameScene::attackVessel() {
  // this->game->validateVesselWeight();
  if (this->selectedAction == ATTACK) {
    // GET CURRENT PLAYER ID FROM GAME
    int currentPlayer = PLAYER_1; // this->game->getCurrentPlayer();

    Coordinates* attackingVesselCoordinates
        = this->board->getCoordinates(currentPlayer);
    int attackerRow = attackingVesselCoordinates->row;
    int attackerCol = attackingVesselCoordinates->col;
    if (attackerRow != NO_COORDINATES && attackerCol != NO_COORDINATES) {
      // CHECK IF COORDINATE IN BACKEND HAS SOMETHING. MUST HAVE A VESSEL
      // this->game->isSlotOccupied(attackerRow, attackerCol);
      Coordinates* attackedVesselCoordinates
        = this->board->getCoordinates((currentPlayer + 1) % 2);
      int victimRow = attackedVesselCoordinates->row;
      int victimCol = attackedVesselCoordinates->col;
      // size_t calculatedDamage = this->game->attackVessel(attackerRow, attackerCol
      //     , victimRow, victimCol);
      // if (this->game->isSlotOccupied(victimRow, vitctimCol))
      //  this->board->draw
          // this->board->removeVesselAt(victimRow, victimCol);
      // this->game->consumeAction();
    }
  }
}

void GameScene::moveVessel() {
  if (this->selectedAction == MOVE) {
    int currentPlayer = PLAYER_1;  // this->game->getCurrentPlayer();
    Coordinates* clicked = this->board->getCoordinates(currentPlayer);
    if (clicked && clicked->row != NONE_SELECTED
        && clicked->col != NONE_SELECTED) {

      if (moveState == MOVE_IDLE) moveState = MOVE_SELECT_VESSEL;

      if (moveState == MOVE_SELECT_VESSEL) {
        if (true /*this->game->isSlotOccupied(clicked->row, clicked->col)*/) {
          moveFrom = *clicked;
          this->board->resetSelection(1);
          moveState = MOVE_SELECT_DESTINATION;
          std::cout << "Now select destination.\n";
        } else {
          std::cout << "No vessel at this slot.\n";
        }
      } else if (moveState == MOVE_SELECT_DESTINATION) {
        if (true /*this->game->isSlotOccupied(clicked->row, clicked->col)*/) {
          this->board->moveVessel(moveFrom.row, moveFrom.col
              , clicked->row, clicked->col);
          std::cout << "Vessel moved.\n";
          moveState = MOVE_IDLE;
          this->selectedAction = NONE_SELECTED;
        } else {
          std::cout << "Destination occupied.\n";
        }
      }
    }
  }
}


void GameScene::upgradeVessel() {
  // this->game->validateVesselWeight();
  if (this->selectedAction == UPGRADE) {
    // GET CURRENT PLAYER ID FROM GAME
    int currentPlayer = PLAYER_1; // this->game->getCurrentPlayer();

    Coordinates* upgradingVesselCoordinates
        = this->board->getCoordinates(currentPlayer);
    int row = upgradingVesselCoordinates->row;
    int col = upgradingVesselCoordinates->col;
    if (row != NO_COORDINATES && col != NO_COORDINATES) {
      // CHECK IF COORDINATE IN BACKEND HAS SOMETHING. MUST HAVE A VESSEL
      // this->game->isSlotOccupied(row, col);
      // this->game->upgradeVessel(row, col);
    }
  }
}
