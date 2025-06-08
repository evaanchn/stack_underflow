// Copyright 2025 stack_underflow CC-BY 4.0

#include "App.hpp"

App::App()
  : appActive(true)
  , gameActive(false)
  , currentState(SceneState::START)
  , startScene()
  , informationScene()
  , gameOverScene()
  , startSceneMusic(MUSIC_FOLDER + "startScene.wav", LOOP)
  , informationSceneMusic(MUSIC_FOLDER + "informationScene.wav", LOOP)
  , gameSceneMusic(MUSIC_FOLDER + "gameScene.wav", LOOP)
  , gameOverSceneMusic(MUSIC_FOLDER + "gameOverScene.wav", LOOP)
  , buttonClickSound(SOUNDS_FOLDER + "soundButtonClick.wav", !LOOP) {
  setMainWindow();
}

App::~App() {
  if (this->gameScene) delete this->gameScene;
  this->gameScene = nullptr;
}

void App::setMainWindow() {
  if (!mainWindow.isOpen()) {
    mainWindow.create(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)
        , GAME_NAME);
  }
}

int App::run() {
  int error = EXIT_SUCCESS;
  while (this->appActive) {
    if (!this->gameActive) {
      this->runMainWindow();
    } else {
      error = this->startGame();
      if (error != EXIT_SUCCESS) return error;
      error = gameScene->run();
      this->endGame();  /*Volume*/
    }
  }
  return error;
}

void App::runMainWindow() {
  while (mainWindow.isOpen()) {
      sf::Event event;
      while (mainWindow.pollEvent(event)) {
          handleGlobalEvents(mainWindow, event);
          handleStateEvents(event);
      }

      mainWindow.clear();
      handleStateRendering();
      mainWindow.display();
  }
}

void App::handleGlobalEvents(sf::RenderWindow& window, sf::Event& event) {
  if (event.type == sf::Event::Closed) {
      window.close();
      appActive = false;
  }
}

void App::handleStateEvents(sf::Event& event) {
  if (currentState == START) startScene.handleEvent(this->mainWindow, event
      , this->currentState, this->gameActive, this->buttonClickSound);
  else if (currentState == INFORMATION) informationScene.handleEvent(
      this->mainWindow, event, this->currentState, this->appActive
      , this->buttonClickSound);
  else if (currentState == GAME_OVER) gameOverScene.handleEvent(this->mainWindow
      , event, this->currentState, this->appActive, this->buttonClickSound);
}

void App::handleStateRendering() {
  if (this->currentState == START) renderStartScene();
  else if (this->currentState == INFORMATION) renderInformationScene();
  else if (this->currentState == GAME_OVER) renderGameOverScene();
}

void App::renderStartScene() {
  informationSceneMusic.stop();
  gameOverSceneMusic.stop();
  startSceneMusic.play();
  startScene.draw(mainWindow);
}

void App::renderInformationScene() {
  startSceneMusic.pause();
  informationSceneMusic.play();
  informationScene.draw(mainWindow);
}

void App::renderGameOverScene() {
  gameOverSceneMusic.play();
  gameOverScene.draw(mainWindow);
}

int App::startGame() {
  this->startSceneMusic.stop();
  this->gameSceneMusic.play();
  try {
    this->gameScene = new GameScene(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT
      , GAME_NAME);
    if (!this->gameScene) throw std::runtime_error(
        "GameScene instance could not be created.");
    this->gameActive = ACTIVE;
  } catch (const std::exception& e) {
    std::cerr << "App:" << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void App::endGame() {
  this->gameSceneMusic.stop();
  this->gameActive = !ACTIVE;
  if (this->gameScene) delete this->gameScene;
  this->gameScene = nullptr;
  this->setMainWindow();
  this->currentState = SceneState::GAME_OVER;
}
