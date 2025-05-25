// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <functional>
#include <stdlib.h>

struct Coordinates {
  size_t row;
  size_t col;
  Coordinates(size_t row, size_t col): row(row), col(col) {}
};

// Custom hash specialization for Coordinates* so it works as a key
// in unordered_map (just in case it is used)
struct CoordinatesPtrHash {
  std::size_t operator()(const Coordinates* coordinates) const {
    return std::hash<size_t>()(coordinates->row)
        ^ (std::hash<size_t>()(coordinates->col) << 1);
  }
};
