// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <unordered_set>
#include "algorithm.hpp"

class b_tree : public algorithm {
 public:
    /// @brief método constructor de la clase
    b_tree();
 private:
    Node root;
};
