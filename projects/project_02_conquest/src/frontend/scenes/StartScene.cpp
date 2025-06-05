// Copyright 2025 stack_underflow CC-BY 4.0

#include "StartScene.hpp"

StartScene::StartScene()
  : background(BACKGROUNDS_FOLDER + "startScene.png",
      Positions::SCENES, Sizes::SCENES)
  , startButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::START_BUTTON, Positions::BUTTON_START
      , RADIUS_REGULAR_BUTTON, CORNERS_REGULAR_BUTTON, 0
      , sf::Color::Transparent)
  , infoButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::START_BUTTON, Positions::BUTTON_INFO
      , RADIUS_REGULAR_BUTTON, CORNERS_REGULAR_BUTTON
      , 0, sf::Color::Transparent) {}

void StartScene::handleEvent(sf::RenderWindow& window, sf::Event& event,
    SceneState& currentState, bool& gameActive/*, SFMLSound &buttonClickSound*/) {
  if (startButton.isMouseOver(window) &&
      event.type == sf::Event::MouseButtonPressed) {
    // buttonClickSound.play();
    currentState = GAME;
    gameActive = ACTIVE;
    window.close();
  } else if (infoButton.isMouseOver(window) &&
      event.type == sf::Event::MouseButtonPressed) {
    // buttonClickSound.play();
    currentState = INFORMATION;
  }
}

void StartScene::draw(sf::RenderWindow& window) {
  background.draw(window);
}