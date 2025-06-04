// Copyright 2025 stack_underflow CC-BY 4.0

#include "StartScene.hpp"

StartScene::StartScene()
  : background(BACKGROUNDS_FOLDER + "startScene.png",
      Positions::SCENES, Sizes::SCENES) {}

void StartScene::handleEvent(sf::RenderWindow& window, sf::Event& event,
    SceneState& currentState) {
  // pending
}

void StartScene::draw(sf::RenderWindow& window) {
  background.draw(window);
}
