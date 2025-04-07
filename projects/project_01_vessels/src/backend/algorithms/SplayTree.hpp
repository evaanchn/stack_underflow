// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include "Algorithm.hpp"

class splayTree : public algorithm {
 public:
    /// @brief constructor method of the class
    splayTree();

    /**
     @brief assigned method for inserting elements
     @param element element to insert
     @return the number of iterations made for the insertion process
    */
    size_t insert(int64_t element) override;

    /**
     @brief method assigned to search for elements
     @see insert
    */
    size_t search(int64_t element) override;

    /**
     @brief method assigned for removing elements
     @see insert
    */
    size_t remove(int64_t element) override;

 private:
    // Node root;
};
