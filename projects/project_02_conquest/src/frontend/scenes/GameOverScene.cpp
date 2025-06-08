// Copyright 2025 stack_underflow CC-BY 4.0

#include "GameOverScene.hpp"

GameOverScene::GameOverScene()
  : background(BACKGROUNDS_FOLDER + "gameOverScene.png",
      Positions::SCENES, Sizes::SCENES)
  , restartButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::GAMEOVER_BUTTON, Positions::BUTTON_RESTART
      , RADIUS_REGULAR_BUTTON, CORNERS_REGULAR_BUTTON
      , 0, sf::Color::Transparent)
  , exitButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
    Sizes::GAMEOVER_BUTTON, Positions::BUTTON_EXIT
    , RADIUS_REGULAR_BUTTON, CORNERS_REGULAR_BUTTON
    , 0, sf::Color::Transparent) {}

void GameOverScene::handleEvent(sf::RenderWindow& window, sf::Event& event,
    SceneState& currentState, bool& appActive, SFMLSound &buttonClickSound) {
  if (restartButton.isMouseOver(window) &&
      event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    currentState = START;
  } else if (exitButton.isMouseOver(window) &&
    event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    appActive = false;
    window.close();
  }
}

void GameOverScene::draw(sf::RenderWindow& window) {
  background.draw(window);
  restartButton.draw(window);
  exitButton.draw(window);
}