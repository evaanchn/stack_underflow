// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

class algorithm {
 public:
  /// @brief constructor method of the algorithm class
  algorithm();

  /// @brief destructor method of the algorithm class
  ~algorithm();

  /**
   @brief assigned method for inserting elements
   @param element element to insert
   @return the number of iterations made for the insertion process
   */
  virtual size_t insert(int64_t element) = 0;

  /**
   @brief method assigned to search for elements
   @see insert
   */
  virtual size_t search(int64_t element) = 0;

  /**
   @brief method assigned for removing elements
   @see insert
   */
  virtual size_t remove(int64_t element) = 0;

 protected:
  std::string algorithmName;
  size_t elementCount;
  std::unordered_set<int64_t> elementRecord;
};
