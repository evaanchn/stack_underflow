// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>

#define ACTIVE true

// BACKGROUND
const std::string SCENES_BACKGROUND_PATH = "assets/scenes_backgrounds/";
const std::string GAME_SCENE_BACKGROUND = SCENES_BACKGROUND_PATH
    + "gameScene.png";

// LABELS
#define LABELS_X 70
#define LONG_LABEL_BOX_W 300
#define LABEL_BOX_W 100
#define LABEL_BOX_H 70

// ACTIONS
enum ACTIONS {
  NO_ACTION = -1, PROBE, EXPLORE, ATTACK
};

#define ACTION_BUTTONS_X 60
#define ACTION_BUTTON_W 150
#define ACTION_BUTTON_H 50

// VESSELS
#define NONE_SELECTED -1
#define VESSEL_BUTTON_DIM 100
// X Positions
#define VESSEL_X_LEFT   240
#define VESSEL_X_RIGHT  360

// Y Positions
#define VESSEL_Y_TOP    270
#define VESSEL_Y_MID    320
#define VESSEL_Y_BOTTOM 370
#define VESSEL_HIDDEN true

const std::string VESSELS_SPRITES_PATH = "assets/sprites/spaceVessel/";

const std::vector<std::string> VESSELS_DATA = {
    "Algorithm: BFS\nCost: 10", "Algorithm: DFS\nCost: 10"
    , "Algorithm: Dijkstra\nCost: 20", "Algorithm: Floyd\nCost: 30"
    , "Algorithm: Greedy Search\nCost: 35", "Algorithm: Local Search\nCost: 40"
    , "Algorithm: Exhaustive Search\nCost: 45", "Algorithm: Exhaustive Prune\nCost: 50"
};