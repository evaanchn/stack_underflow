// Copyright 2025 stack_underflow CC-BY 4.0

#include <iostream>
#include <SFML/Graphics.hpp>

#include "ActionLog.hpp"
#include "Board.hpp"
#include "Simulation.hpp"
#include "Vessel.hpp"
#include "RedBlackTree.hpp"

void vesselMenu(Board& board, int playerID);

int main(void) {
  Simulation* simulation = new Simulation();
  simulation->simulate();
  delete simulation;
  return EXIT_SUCCESS;
}
