// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "Button.hpp"
#include "SFMLImage.hpp"
#include "SFMLSound.hpp"
#include "ScenesConstants.hpp"

#include "Simulation.hpp"

class InformationScene {
 public:
  InformationScene();
  void handleEvent(sf::RenderWindow& window, sf::Event& event,
      SceneState& currentState, bool& appActive/*, SFMLSound &buttonClickSound*/);
  void draw(sf::RenderWindow& window);

 private:
  SFMLImage background;
  Button backButton;
  Button exitButton;
};
