// Copyright 2025 stack_underflow CC-BY 4.0

#include <iostream>
#include <SFML/Graphics.hpp>

#include "App.hpp"

const char* const usage =
  "Usage: spaceOps [galaxy.csv] [operationNumber] [outputFolder]"
  " [linkProbability]\n"
  "\n"
  "  - galaxy.csv: relative path from the executing folder to the required csv"
  " file\n"
  "  - operationNumber: Number of executions to be done for each algorithm\n"
  "  - outputFolder: {optional} relative path from the executing folder to a"
  "writeable folder to store BattleLog files\n"
  "  - linkProbability: {optional} Number betwen 0-100, modify graph"
  " conectivity level\n";

// TODO(any): move to Simulation class
/**
 * @brief Load command line arguments for a simulation
 * 
 * @param simulation save given arguments
 */
bool analyzeArguments(int argc, char* argv[]/*, Simulation& simulation*/);

/**
 * @brief Start program processing the required arguments to init game
 * 
 * @param argc counter
 * @param argv arguments
 * @return int error code
 */
int main(int argc, char* argv[]) {
  if (argc > 1) {  // not only program name
    // Simulation simulation;
    if (analyzeArguments(argc, argv/*, simulation*/)) {
      // return simulation.run();
    }
    return EXIT_FAILURE;
  }
  return App().run();
}

bool analyzeArguments(int argc, char* argv[]/*, Simulation& simulation*/) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }
  std::string galaxyCSVPath;
  size_t operationsNumber = 0;
  std::string outputFolder;
  size_t linkProbability = 0;

  if (argc < 3) {
    return false;
  }
  // required arguments
  galaxyCSVPath = argv[1];
  try {
    operationsNumber = std::stoul(argv[2]);
  } catch(const std::invalid_argument& error) {
    std::cerr << "Warning: " << error.what()
      << std::endl << usage;
    return false;
  }
  // optional arguments
  if (argc >= 4) outputFolder = argv[3];
  if (argc >= 5) {
    try {
      linkProbability = std::stoul(argv[4]);
    } catch(const std::invalid_argument& error) {
      std::cerr << "Warning: " << error.what()
        << std::endl << usage;
      return false;
    }
  } else {
    linkProbability = 50/*LINK_PROBABILITY*/;
  }
  return (operationsNumber > 0 && linkProbability > 0);
}
