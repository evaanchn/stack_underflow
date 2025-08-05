// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <string>

enum SceneState { START, INFORMATION, GAME, GAME_OVER };

namespace Positions {
  const sf::Vector2f SCENES(0, 0);
  const sf::Vector2f BUTTON_START(1073, 490);
  const sf::Vector2f BUTTON_INFO(1073, 600);
  
  const sf::Vector2f BUTTON_SIMULATE(1023, 53);
  const sf::Vector2f BUTTON_MANUAL(1027, 260);
  const sf::Vector2f BUTTON_RETURN(933, 473);
  const sf::Vector2f BUTTON_INFO_EXIT(1120, 473);
  
  const sf::Vector2f BUTTON_RESTART(1033, 197);
  const sf::Vector2f BUTTON_EXIT(1100, 270);
};
  
namespace Sizes {
  const sf::Vector2f SCENES(1280, 720);
  const sf::Vector2f REGULAR_BUTTON(133, 40);
  const sf::Vector2f LARGE_BUTTON(233, 40);
  const sf::Vector2f CIRCULAR_BUTTON(107, 107);
};

#define RADIUS_REGULAR_BUTTON 23
#define CORNERS_REGULAR_BUTTON 13

#define RADIUS_CIRCULAR_BUTTON 30.0f
#define CORNERS_CIRCULAR_BUTTON 23

#define ACTIVE true
#define EMPTY_TEXT ""
#define FONT_PATH_PIXEL "assets/fonts/pixel.ttf"

const std::string BACKGROUNDS_FOLDER = "assets/scenes_backgrounds/";
const std::string MUSIC_FOLDER = "assets/music/";
const std::string GAME_BUTTONS_FOLDER = "assets/sprites/buttons/";

#define ACTION_BUTTON_DIM 67
#define VESSEL_BUTTON_DIM 67

#define A_BUTTONS_COUNT 4
#define V_BUTTONS_COUNT 6
#define GAME_LABELS_COUNT 5

#define ACTION_BUTTONS_X 1167
#define VESSELS_BUTTON_Y 547

#define LABEL_BOX_W 67
#define LABEL_BOX_H 47
#define LONG_LABEL_BOX_W 200

#define NONE_SELECTED -1

enum Actions { UPGRADE, MOVE, ATTACK, BUY, EXIT, FLAG, UNFLAG };
enum Vessels { NO_VESSEL = -1, SET, RB_TREE, B_TREE, BINARY_SEARCH
    , SPLAY_TREE, LINEAR_SEARCH };
enum MoveState { MOVE_IDLE, MOVE_SELECT_VESSEL, MOVE_SELECT_DESTINATION };

#define VESSELS_COUNT 6
const std::string VESSELS_RIGHT_FOLDER = "assets/sprites/vessels/right/";
const std::string VESSELS_LEFT_FOLDER = "assets/sprites/vessels/left/";
const std::vector<std::string> VESSEL_SPRITES = {
    "Set.png",
    "RedBlackTree.png",
    "BTree.png",
    "BinarySearch.png",
    "SplayTree.png",
    "LinearSearch.png"
};

const std::string SOUNDS_FOLDER = "assets/sounds/";
