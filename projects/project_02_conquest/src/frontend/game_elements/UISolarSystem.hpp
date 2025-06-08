// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Coordinates.hpp"
#include "Graph.hpp"
#include "Random.hpp"
#include "UIPath.hpp"
#include "UIPlanet.hpp"
#include "../backend/galaxy/solar_system/planet/Planet.hpp"

// Window and layout constants
#define WINDOW_WIDTH 1280       ///< Total window width in pixels
#define WINDOW_HEIGHT 720       ///< Total window height in pixels
#define RIGHT_HALF_START_X (WINDOW_WIDTH / 2)  ///< X-coordinate where right half begins
#define MIN_MARGIN 20           ///< Minimum margin around UI elements
#define MIN_PLANET_DISTANCE 30  ///< Minimum distance between planets in pixels
#define DEFAULT_PATH_COLOR FL_BLUE  ///< Default color for paths
#define NONE_SELECTED -1        ///< Constant representing no selected planet

// Layout calculation macros
#define AREA_WIDTH (WINDOW_WIDTH / 2 - MIN_MARGIN * 2)  ///< Width of the interactive area
#define AREA_HEIGHT (WINDOW_HEIGHT - MIN_MARGIN * 2)    ///< Height of the interactive area
#define START_X (RIGHT_HALF_START_X + MIN_MARGIN)       ///< Starting X coordinate for layout

// Sprite paths
const std::string BOSS_SPRITE_PATH = "assets/sprites/boss/Atlas.png";  ///< Path to boss sprite image
const std::string MINE_SPRITE_PATH = "assets/sprites/mine/extractor.png";  ///< Path to mine sprite image

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
  std::unordered_map<Coordinates*, UIPath*> UiPaths;  ///< Map of UI paths between planets
  int selectedPlanet = NONE_SELECTED;  ///< Index of currently selected planet (-1 for none)
  Fl_PNG_Image* mineSprite = nullptr;  ///< Pointer to mine sprite image

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
   * @brief Get the index of the currently selected planet
   * @return int Index of selected planet or NONE_SELECTED (-1)
   */
  int getSelectedPlanet() const;
  
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
  void removeBoss(size_t planetIdx);
};
