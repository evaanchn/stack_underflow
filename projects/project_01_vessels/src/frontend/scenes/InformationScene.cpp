// Copyright 2025 stack_underflow CC-BY 4.0

#include "InformationScene.hpp"

InformationScene::InformationScene()
  : background(BACKGROUNDS_FOLDER + "informationScene.png",
      Positions::SCENES, Sizes::SCENES)
  , simulateButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::CIRCULAR_BUTTON, Positions::BUTTON_SIMULATE
      , RADIUS_CIRCULAR_BUTTON, CORNERS_CIRCULAR_BUTTON, 0
      , sf::Color::Transparent)
  , manualButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::CIRCULAR_BUTTON, Positions::BUTTON_MANUAL
      , RADIUS_CIRCULAR_BUTTON, CORNERS_CIRCULAR_BUTTON
      , 0, sf::Color::Transparent)
  , returnButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::CIRCULAR_BUTTON, Positions::BUTTON_RETURN
      , RADIUS_CIRCULAR_BUTTON, CORNERS_CIRCULAR_BUTTON, 0
      , sf::Color::Transparent)
  , exitButton(EMPTY_TEXT, FONT_PATH_PIXEL, sf::Color::Transparent,
      Sizes::CIRCULAR_BUTTON, Positions::BUTTON_INFO_EXIT
      , RADIUS_CIRCULAR_BUTTON, CORNERS_CIRCULAR_BUTTON, 0
      , sf::Color::Transparent) {}

void InformationScene::handleEvent(sf::RenderWindow& window, sf::Event& event,
    SceneState& currentState, bool& appActive, SFMLSound &buttonClickSound) {
  if (simulateButton.isMouseOver(window) &&
      event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    Simulation* simulation = new Simulation();
    simulation->simulate();
    delete simulation;
  } else if (manualButton.isMouseOver(window) &&
      event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    system(("xdg-open " + MANUAL_URL).c_str());
  } else if (returnButton.isMouseOver(window) &&
    event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    currentState = START;
  } else if (exitButton.isMouseOver(window) &&
    event.type == sf::Event::MouseButtonPressed) {
    buttonClickSound.play();
    appActive = !ACTIVE;
    window.close();
  }
}

void InformationScene::draw(sf::RenderWindow& window) {
  background.draw(window);
}