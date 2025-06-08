// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <vector>

#include "BattleLog.hpp"
#include "Galaxy.hpp"
#include "Game.hpp"
#include "GameConstants.hpp"
#include "SolarSystem.hpp"

#define MIN_DAMAGE_SIMULATION 1

#define RECORD_ACTIONS true
#define ATTACKS_AVAILABLE 4
#define MAX_ATTACKS 10
enum ATTACKS {
  GREEDY, LOCAL, EXHAUSTIVE, PRUNED
};
const std::string ATTACKS_IDS[ATTACKS_AVAILABLE] =
  { "Greedy"
  , "Local Search"
  , "Exhaustive Search"
  , "Exhaustive Search Pruned"};

/**
 * @class Simulation
 * @brief Manages the simulation of various space vessel operations and records 
 * performance statistics.
 */
class Simulation {
 private:
  /// @brief The game instance that manages the galaxy and player actions.
  Game* game;
  /// @brief Pointer to the BattleLog instance for recording actions.
  BattleLog* battleLog;
  /// @brief The name of the Galaxy CSV file to be loaded.
  std::string galaxyCSVPath = GALAXY_FILE_PATH;
  /// @brief The output folder where BattleLog files will be stored.
  std::string outputFolder;
  /// @brief Flag for deciding whether to record actions or not
  bool recordActions = !RECORD_ACTIONS;

  /// @brief Provides usage instructions for the program.
  const char* const usage =
  "Usage: project_02_conquest galaxy.csv [outputFolder] print\n"
  "\n"
  "  - galaxy.csv: relative path from the executing folder to the required csv"
  " file\n"
  "  - print: {optional} Indicate if specific actions must be printed into"
  "report\n"
  " - outputFolder: {optional} relative path from the executing folder to a"
  "writeable folder to store BattleLog files\n";
 public:
  /// @brief Constructs a Simulation instance.
  /// Initializes the battle log and loads a Galaxy CSV file.
  Simulation();
  /// @brief Class destructor
  ~Simulation();

  /// @brief Loads the arguments from command line and initializes the
  /// simulation
  /// @param argc number of arguments
  /// @param argv arguments
  /// @return bool true if arguments are valid, false otherwise
  bool analyzeArguments(int argc, char* argv[]);

  /// @brief Runs the full simulation objects and starts the tests.
  /// @return int EXIT_SUCCESS on successful execution, EXIT_FAILURE on error.
  int run(int argc, char* argv[]);

 private:
  /// @brief Builds the required objects from the analyzed arguments
  /// @throws std::runtime_error if objects could not be created
  void initSimulation();
  /// @brief Runs tests for probe, scout, and attack operations.
  /// @warning must be called after initSimulation()
  void test();
  /// @brief Perform ramndom actions until the solar system is complete.
  void completeSystemTest();
  void testProbe(std::vector<ActionLog>& BFSLogs
      , std::vector<ActionLog>& DFSLogs);
  void testScout(std::vector<ActionLog>& dijkstraLogs
      , std::vector<ActionLog>& floydLogs);
  void testAttack(std::vector<DamageLog>& GreedyLogs
      , std::vector<DamageLog>& LocalSearchLogs
      , std::vector<DamageLog>& ExhaustiveSearchLogs
      , std::vector<DamageLog>& exhaustiveSearchPruneLogs);
  /// @brief Test executions for various space vessel algorithms.
  /// @return ActionLog object containing the results of the tests.
  ActionLog tesProbingVessel(ProbingVessel<Planet*, size_t>* vessel);
  ActionLog tesScoutingVessel(ScoutingVessel<Planet*, size_t>* vessel);
  DamageLog testAttackVessel(AttackVessel<Planet*, size_t>* vessel, int type);
};
