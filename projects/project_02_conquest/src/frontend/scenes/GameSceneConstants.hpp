// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "GameConstants.hpp"

#define ACTIVE true

// MUSIC
const std::string VESSEL_BUTTON_SOUND_PATH  // NOLINT(runtime/string)
    = "assets/sounds/soundVesselButton.wav";
const std::string SOUND_ACTION_BUTTON_PATH  // NOLINT(runtime/string)
    = "assets/sounds/soundActionButton.wav";
const std::string SOUND_NEW_SYSTEM_PATH  // NOLINT(runtime/string)
    = "assets/sounds/transitionMistery.wav";
const std::string SOUND_ATTACK_PATH  // NOLINT(runtime/string)
    = "assets/sounds/attack.wav";

// BACKGROUND
const std::string SCENES_BACKGROUND_PATH = "assets/scenes_backgrounds/";
const std::string GAME_SCENE_BACKGROUND  // NOLINT(runtime/string)
    = "assets/scenes_backgrounds/gameScene.png";

// LABELS
#define LABELS_X 70
#define LONG_LABEL_BOX_W 300
#define LABEL_BOX_W 100
#define LABEL_BOX_H 70

#define ACTION_BUTTONS_X 60
#define ACTION_BUTTON_W 150
#define ACTION_BUTTON_H 50

// VESSELS
#define BLOCKED -2
#define NONE_SELECTED -1
#define VESSEL_BUTTON_DIM 100
// X Positions
#define VESSEL_X_LEFT   240
#define VESSEL_X_RIGHT  360

// Y Positions
#define VESSEL_Y_TOP    260
#define VESSEL_Y_MID    320
#define VESSEL_Y_BOTTOM 380
#define VESSEL_HIDDEN true

const std::string VESSELS_SPRITES_PATH = "assets/sprites/spaceVessel/";
const std::vector<std::string> VESSELS_LABELS = {
    "Rapid Sight", "Deep Probe"
    , "Path Finder", "Star Mapper"
    , "Raider", "Forager"
    , "Wayfarer", "Oracle"
};

#define ALREADY_SELECTED(selectedVesselIndex) \
  VESSELS_LABELS[selectedVesselIndex] \
    + " already selected\n" \
    + "Click on a planet"

const std::vector<std::string> VESSELS_DATA = {
  "Algorithm: BFS\nCost: " +  std::to_string(BFS_COST)
  , "Algorithm: DFS\nCost: " +  std::to_string(DFS_COST)
  , "Algorithm: Dijkstra\nCost: " +  std::to_string(DIJKSTRA_COST)
  , "Algorithm: Floyd\nCost: " +  std::to_string(FLOYD_COST)
  , "Algorithm: Greedy Search\nCost: " +  std::to_string(GREEDY_COST)
  , "Algorithm: Local Search\nCost: " +  std::to_string(LOCALSEARCH_COST)
  , "Algorithm: Exhaustive Search\nCost: " +  std::to_string(EXHAUSTIVE_COST)
  , "Algorithm: Exhaustive Prune\nCost: "
    +  std::to_string(EXHAUSTIVEPRUNE_COST)
};
