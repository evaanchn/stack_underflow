// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <string>
#include <unordered_set>

#include "Algorithm.hpp"

class Hashset : public Algorithm {
 public:
  Hashset();
  size_t insert(int64_t element) override;
  size_t search(int64_t element) override;
  size_t remove(int64_t element) override;

 private:
  std::unordered_set<int64_t> hashset;
};
