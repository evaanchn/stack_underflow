// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

class Algorithm {
 public:
  /// @brief constructor method of the algorithm class
  Algorithm();

  /// @brief destructor method of the algorithm class
  virtual ~Algorithm();

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
  /**
   * @brief Get name attribute
   * 
   * @return std::string 
   */
  std::string getName();

  virtual size_t getElementCount();

 protected:
  std::string algorithmName = " ";
  size_t elementCount = 0;
  std::unordered_set<int64_t> elementRecord = std::unordered_set<int64_t>();
};
