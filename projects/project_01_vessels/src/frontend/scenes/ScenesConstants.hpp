// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

#define ACTIVE true
#define EMPTY_TEXT ""
#define FONT_PATH_PIXEL "assets/fonts/pixel.ttf"

const std::string BACKGROUNDS_FOLDER = "assets/scenes_backgrounds/";
const std::string MUSIC_FOLDER = "assets/music/";
const std::string GAME_BUTTONS_FOLDER = "assets/sprites/buttons/";

#define ACTION_BUTTON_DIM 100
#define VESSEL_BUTTON_DIM 100

#define A_BUTTONS_COUNT 4
#define V_BUTTONS_COUNT 6
#define GAME_LABELS_COUNT 5

#define ACTION_BUTTONS_X 1750
#define VESSELS_BUTTON_Y 820

const Fl_Color GAME_BACKGROUND = fl_rgb_color(5, 10, 48);
const Fl_Color VESSELS_BACKGROUND = fl_rgb_color(143, 209, 230);
#define LABEL_BOX_W 50
#define LABEL_BOX_H 18

#define NONE_SELECTED -1

enum Actions { UPGRADE, MOVE, ATTACK, BUY};
enum Vessels { NO_VESSEL = -1, SET, RB_TREE, BTREE, BINARY_SEARCH
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