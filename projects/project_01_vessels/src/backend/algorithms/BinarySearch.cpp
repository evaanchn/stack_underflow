// Copyright 2025 stack_underflow CC-BY 4.0

#include "BinarySearch.hpp"

BinarySearch::BinarySearch(): Algorithm()
, arraySize(DEFAULT_ARRAY_SIZE)
, orderedArray(nullptr) {
  this->algorithmName = "Binary Search";
  this->elementCount = 0;
  this->orderedArray = reinterpret_cast<int64_t*>
    (calloc(this->arraySize, sizeof(int64_t)));
  if (this->orderedArray == nullptr) {
    throw std::bad_alloc();
  }
}

BinarySearch::~BinarySearch() {
  if (this->orderedArray != nullptr) {
    free(this->orderedArray);
    this->orderedArray = nullptr;
  }
}

size_t BinarySearch::insert(int64_t element) {
  size_t iterations = 0;
  // check if array is full
  if (this->elementCount >= this->arraySize) {
    throw std::runtime_error("BinarySearch: can not insert more elements\n");
  }
  this->insertInPlace(element, iterations);
  this->elementRecord.insert(element);
  ++this->elementCount;
  return iterations;
}

void BinarySearch::insertInPlace(int64_t element, size_t& iterations) {
  if (this->elementCount >= this->arraySize) {
    throw std::bad_alloc();
  }
  if (this->elementCount  == 0) {
    this->orderedArray[0] = element;
    ++iterations;
  // can insert at the end
  } else if (this->orderedArray[elementCount - 1] <= element) {
    this->orderedArray[elementCount] = element;
    ++iterations;
  // shift
  } else {
    size_t index = 0;
    // find index to insert element
    while (index < this->elementCount) {
      if (this->orderedArray[index] <= element) {
        break;
      }
      ++index;
      ++iterations;
    }
    // shift elements after index
    int64_t shiftElement = 0;
    for (size_t i = index; i <= elementCount; ++i) {
      shiftElement = this->orderedArray[i];
      this->orderedArray[i] = element;
      element = shiftElement;
      ++iterations;
    }
  }
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
    return 0;
  }
  int index = search(element, iterations);
  if (index == -1) {  // not found
    return 0;
  }
  // reallocate
  for (size_t i = index; i < this->elementCount - 1; ++i) {
    this->orderedArray[i] = this->orderedArray[i+1];
    ++iterations;
  }
  this->orderedArray[elementCount - 1] = 0;  // clean deallocated index
  --this->elementCount;
  this->elementRecord.erase(element);
  return iterations;
}

void BinarySearch::loadRangeValues(int64_t min, int64_t max) {
  size_t count = std::abs(max - min) + 1;
  if (count > this->arraySize) {
    throw std::bad_array_new_length();
  }
  for (size_t index = 0; index < count; index++) {
    this->orderedArray[index] = min + index;
    ++this->elementCount;
  }
}
