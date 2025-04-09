// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "Button.hpp"
#include "SFMLImage.hpp"
#include "SFMLSound.hpp"
#include "ScenesConstants.hpp"

class GameOverScene {
 public:
  GameOverScene();
  void handleEvent(sf::RenderWindow& window, sf::Event& event,
      SceneState& currentState, bool& appActive);
  void draw(sf::RenderWindow& window);

 private:
  SFMLImage background;
  Button restartButton;
  Button exitButton;
};
