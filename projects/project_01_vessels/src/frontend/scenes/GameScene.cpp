// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameScene.hpp"

GameScene::GameScene(int width, int height, const std::string& title) {
  this->gameActive = ACTIVE;
  window = new Fl_Window(width, height, title.c_str());
  this->setupUI();
  this->window->end();  // Ends window's elements' grouping
  this->window->show();
}

GameScene::~GameScene() {
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
  // SET BOARD
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
      , GAME_BUTTONS_FOLDER + "buyRune.png", EMPTY_TEXT);
  setActionButtonCallBack(buyButton, BUY);

  attackButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 385
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "attackRune.png", EMPTY_TEXT);
  setActionButtonCallBack(attackButton, ATTACK);

  moveButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 540
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "moveRune.png", EMPTY_TEXT);
  setActionButtonCallBack(moveButton, MOVE);

  upgradeButton = new CustomIconButton(ACTION_BUTTONS_X, /*Y*/ 700
      , ACTION_BUTTON_DIM, ACTION_BUTTON_DIM
      , GAME_BUTTONS_FOLDER + "upgradeRune.png", EMPTY_TEXT);
  setActionButtonCallBack(upgradeButton, UPGRADE);
}

void GameScene::setVesselButtons() {
  hashsetButton = new CustomIconButton(/*X*/ 1190, VESSELS_BUTTON_Y + 10
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "Set.png", EMPTY_TEXT);
  setVesselButtonCallBack(hashsetButton, SET);

  redBlackButton = new CustomIconButton(/*X*/ 980, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "RedBlackTree.png", EMPTY_TEXT);
  setVesselButtonCallBack(redBlackButton, RB_TREE);

  bTreeButton = new CustomIconButton(/*X*/ 765, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "BTree.png", EMPTY_TEXT);
  setVesselButtonCallBack(bTreeButton, BTREE);

  binarySearchButton = new CustomIconButton(/*X*/ 550, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "BinarySearch.png", EMPTY_TEXT);
  setVesselButtonCallBack(binarySearchButton, BINARY_SEARCH);

  splayButton = new CustomIconButton(/*X*/ 355, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "SplayTree.png", EMPTY_TEXT);
  setVesselButtonCallBack(splayButton, SPLAY_TREE);

  linearSearchButton = new CustomIconButton(/*X*/ 155, VESSELS_BUTTON_Y
    , VESSEL_BUTTON_DIM, VESSEL_BUTTON_DIM
    , VESSELS_FOLDER + "LinearSearch.png", EMPTY_TEXT);
  setVesselButtonCallBack(linearSearchButton, LINEAR_SEARCH);
}

void GameScene::setActionButtonCallBack(CustomIconButton* button, int data) {
  button->set_click_callback([this, data]() { this->selectedAction = data; });
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

int GameScene::run() {
  // Game logic and redraws can go here
  while (gameActive) {
    Fl::check();   // Process events
    Fl::wait(0.02); // Add a small delay to prevent CPU overuse
    if (!this->window->visible()) { this->gameActive = !ACTIVE; }
  }
  return Fl::run();
}
