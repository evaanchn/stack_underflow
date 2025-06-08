// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SFMLSound.hpp"

#include "Coordinates.hpp"
#include "Graph.hpp"
#include "Random.hpp"
#include "UIPath.hpp"
#include "UIPlanet.hpp"
#include "../backend/galaxy/solar_system/planet/Planet.hpp"


// Window and layout constants
///< Total window width in pixels
#define WINDOW_WIDTH 1280
///< Total window height in pixels
#define WINDOW_HEIGHT 720
///< X-coordinate where right half begins
#define RIGHT_HALF_START_X (WINDOW_WIDTH / 2)
///< Minimum margin around UI elements
#define MIN_MARGIN 20
///< Minimum distance between planets in pixels
#define MIN_PLANET_DISTANCE 30
///< Default color for paths
#define DEFAULT_PATH_COLOR FL_BLUE
///< Constant representing no selected planet
#define NONE_SELECTED -1

// Layout calculation macros
///< Width of the interactive area
#define AREA_WIDTH (WINDOW_WIDTH / 2 - MIN_MARGIN * 2)
///< Height of the interactive area
#define AREA_HEIGHT (WINDOW_HEIGHT - MIN_MARGIN * 2)
///< Starting X coordinate for layout
#define START_X (RIGHT_HALF_START_X + MIN_MARGIN)

// Sprite paths
///< Path to boss sprite image
const std::string BOSS_SPRITE_PATH = "assets/sprites/boss/Atlas.png";
///< Path to mine sprite image
const std::string MINE_SPRITE_PATH = "assets/sprites/mine/extractor.png";

// Sounds path
const std::string SOUND_PLANET_SELECTED = "assets/sounds/planetSelectedSound.wav";

/**
 * @class UISolarSystem
 * @brief Manages the visual representation of a solar system in the UI
 *
 * This class handles the display and interaction with planets and paths
 * between them in a solar system view. It maintains the state of selected
 * planets and manages visibility of system elements.
 */
class UISolarSystem {
 private:
  std::vector<UIPlanet*> UiPlanets;  ///< Vector of UI planet objects
  std::vector<std::vector<UIPath*>> UiPaths;
  ///< Index of currently selected planet (-1 for none)
  int selectedPlanet = NONE_SELECTED;
  Fl_PNG_Image* mineSprite = nullptr;  ///< Pointer to mine sprite image
  SFMLSound planetSelectedSound;  // planet interaction sound

 public:
  /**
   * @brief Construct a new UISolarSystem object
   */
  UISolarSystem();

  /**
   * @brief Destroy the UISolarSystem object
   * Cleans up allocated resources
   */
  ~UISolarSystem();

  /**
   * @brief Create UI planet objects from backend planet data
   * @param planets Vector of Planet objects from the backend
   */
  void createPlanets(std::vector<Planet*> planets);

  /**
   * @brief Create UI paths between planets based on graph connections
   * @param graph Graph structure containing planet connections
   * @param container FLTK container widget for the paths
   */
  void createPaths(Graph<Planet*, size_t>* graph, Fl_Group* container);

  /**
   * @brief Get the index of the currently selected planet and restart to NONE
   * @return int Index of selected planet or NONE_SELECTED (-1)
   */
  int obtainSelectedPlanet();

  /**
   * @brief Update visibility of paths based on exploration state
   * @param pathsRevealed 2D vector indicating which paths should be visible
   */
  void updatePathsVisibility(std::vector<std::vector<bool>>& pathsRevealed);

  /**
   * @brief Update visibility of planets based on exploration state
   * @param exploredPlanets Set of planets that have been explored
   * @param planets Vector of all planets in the system
   */
  void updatePlanetsVisibility(std::unordered_set<Planet*> exploredPlanets,
                              std::vector<Planet*> planets);

  /**
   * @brief Reveal a specific planet in the UI
   * @param planetIdx Index of the planet to reveal
   */
  void revealPlanet(size_t planetIdx);

  /**
   * @brief Remove boss representation from a planet
   * @param planetIdx Index of the planet to remove boss from
   */
  void removeBoss(int planetIdx);
};
