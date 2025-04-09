// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>

enum SceneState {
    START,
    INFORMATION,
    GAME,
    GAME_OVER
};

namespace Positions {
  const sf::Vector2f SCENES(0, 0);
  const sf::Vector2f BUTTON_START(1610, 735);
  const sf::Vector2f BUTTON_INFO(1610, 900);

  const sf::Vector2f BUTTON_RESTART(1550, 295);
  const sf::Vector2f BUTTON_EXIT(1655, 405);

};

namespace Sizes {
  const sf::Vector2f SCENES(1920, 1080);
  const sf::Vector2f REGULAR_BUTTON(200, 60);
  const sf::Vector2f LARGE_BUTTON(350, 60);
};

#define RADIUS_REGULAR_BUTTON 35
#define CORNERS_REGULAR_BUTTON 20

#define EMPTY_TEXT ""
#define FONT_PATH_PIXEL "assets/fonts/pixel.ttf"

const std::string BACKGROUNDS_FOLDER = "assets/scenes_backgrounds/";
const std::string MUSIC_FOLDER = "assets/music/";