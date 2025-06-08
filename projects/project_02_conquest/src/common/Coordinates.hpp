// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <functional>

struct Coordinates {
  size_t row;
  size_t col;

  constexpr Coordinates(size_t r, size_t c) noexcept : row(r), col(c) {}

  constexpr bool operator==(const Coordinates& other) const noexcept {
    return row == other.row && col == other.col;
  }
};

// Custom hash specialization for Coordinates* so it works as a key
// in unordered_map (just in case it is used)
struct CoordinatesHash {
  std::size_t operator()(const Coordinates& c) const {
    // A common and good-enough hash combiner
    return std::hash<size_t>()(c.row) ^ (std::hash<size_t>()(c.col) << 1);
  }
};
