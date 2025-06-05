// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <SFMLRectangle.hpp>

enum SceneState {
    START,
    INFORMATION,
    GAME,
    GAME_OVER
};

namespace Positions {
  const sf::Vector2f SCENES(0, 0);
  const sf::Vector2f BUTTON_START(1090, 480);
  const sf::Vector2f BUTTON_INFO(1090, 600);
  const sf::Vector2f BUTTON_INFO_BACK(35, 30);
  const sf::Vector2f BUTTON_INFO_EXIT(1175, 665);
  const sf::Vector2f BUTTON_RESTART(540, 380);
  const sf::Vector2f BUTTON_EXIT(540, 490);
};

namespace Sizes {
  const sf::Vector2f SCENES(1280, 720);
  const sf::Vector2f START_BUTTON(200, 60);
  const sf::Vector2f INFO_BUTTON(100, 30);
  const sf::Vector2f GAMEOVER_BUTTON(200, 60);

};

#define RADIUS_REGULAR_BUTTON 35
#define CORNERS_REGULAR_BUTTON 20

#define RADIUS_CIRCULAR_BUTTON 45.0f
#define CORNERS_CIRCULAR_BUTTON 35

#define ACTIVE true
#define EMPTY_TEXT ""
#define FONT_PATH_PIXEL "assets/fonts/pixel.ttf"

const std::string BACKGROUNDS_FOLDER = "assets/scenes_backgrounds/";
const std::string MUSIC_FOLDER = "assets/music/";
const std::string SOUNDS_FOLDER = "assets/sounds/";

