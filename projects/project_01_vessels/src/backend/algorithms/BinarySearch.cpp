// Copyright 2025 stack_underflow CC-BY 4.0

#include "BinarySearch.hpp"

BinarySearch::BinarySearch(): algorithm()
, arraySize(DEFAULT_ARRAY_SIZE) {
  this->algorithmName = "BinarySearch";
  this->elementCount = 0;
  this->orderedArray = reinterpret_cast<int64_t*>
    (calloc(this->arraySize, sizeof(int64_t)));
  if (this->orderedArray == nullptr) {
    throw std::bad_alloc();
  }
  // default array values
  loadRangeValues(1, this->arraySize / 2);
}

BinarySearch::~BinarySearch() {
  free(this->orderedArray);
}

size_t BinarySearch::insert(int64_t element) {
  size_t iterations = 0;
  if (this->elementCount >= this->arraySize -1) {
    throw std::bad_alloc();
  }
  this->orderedArray[elementCount] = element;
  ++this->elementCount;
  // sort not implemented because it is not relevant for the present project
  std::sort(this->orderedArray, this->orderedArray
    + this->elementCount * sizeof(int64_t));
  return iterations;
}

size_t BinarySearch::search(int64_t element) {
  size_t iterations = 0;
  search(element, iterations);
  return iterations;
}

int BinarySearch::search(int64_t element, size_t& iterations) {
  int begin = 0;
  int end = this->elementCount - 1;
  int index = -1;
  while (begin <= end) {
    index = (begin + end) / 2;
    ++iterations;
    if (this->orderedArray[index] == element) {
      // found
      return index;
    }
    if (this->orderedArray[index] < element) {
      begin = index + 1;
      continue;
    }
    if (this->orderedArray[index] > element) {
      end = index - 1;
      continue;
    }
  }
  // not found
  return -1;
}

size_t BinarySearch::remove(int64_t element) {
  size_t iterations = 0;
  if (elementRecord.find(element) == elementRecord.end()) {
    return iterations;
  }
  int index = search(element, iterations);
  if (index == -1) {  // not found
    return iterations;
  }
  // reallocate
  for (size_t i = index; i < this->elementCount - 2; ++i) {
    this->orderedArray[i] = this->orderedArray[i+1];
    ++iterations;
  }
  --this->elementCount;
  return iterations;
}

void BinarySearch::loadRangeValues(int64_t min, int64_t max) {
  size_t count = abs(max - min) + 1;
  if (count > this->arraySize) {
    throw std::bad_array_new_length();
  }
  for (size_t index = 0; index < count; index++) {
    this->orderedArray[index] = min + index;
    ++this->elementCount;
  }
}
