// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>

struct Player {
  size_t purchasePoints;
  size_t upgradePoints;
  size_t totalVesselWeight;
};

class Game {
 public:
 private:
  bool gameOver;
  int64_t winner;
  int64_t currentPlayer;
};
