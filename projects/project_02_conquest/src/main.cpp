// Copyright 2025 stack_underflow CC-BY 4.0

#include <iostream>

#include "Simulation.hpp"

/**
 * @brief Start program processing the required arguments to init game
 * 
 * @param argc counter
 * @param argv arguments
 * @return int error code
 */
int main(int argc, char* argv[]) {
  if (argc > 1) {  // not only program name
    Simulation simulation;
    std::cout << "Starting simulation..." << std::endl;
    return simulation.run(argc, argv);
  }
  return EXIT_SUCCESS/*App().run();*/;
}
