// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <stdexcept>

#include "Algorithm.hpp"

#define DEFAULT_ARRAY_SIZE 100

class BinarySearch: public Algorithm {
 public:
  BinarySearch();
  // Disable copy and move
  BinarySearch(const BinarySearch& other) = delete;
  BinarySearch(BinarySearch&& other) = delete;
  BinarySearch& operator=(const BinarySearch& other) = delete;
  BinarySearch& operator=(BinarySearch&& other) = delete;
  ~BinarySearch();

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
   * @brief Recursive binary search process
   * 
   * @param element target
   * @param iterations counter of recursions
   * @return index where element was found
   * @return -1 if element was not found
   */
  int search(int64_t element, size_t& iterations);

  /**
  @brief method assigned for removing elements
  @see insert
  */
  size_t remove(int64_t element) override;

  int64_t* allocateArray(size_t size);

 private:
  /**
   * @brief Load the array with the values between the give range
   * 
   * @param min 
   * @param max 
   */
  void loadRangeValues(int64_t min, int64_t max);

  void insertInPlace(int64_t element, size_t& iterations);

 private:
  size_t arraySize;
  int64_t* orderedArray;
};
