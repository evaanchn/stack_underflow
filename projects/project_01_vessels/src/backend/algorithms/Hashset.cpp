// Copyright 2025 stack_underflow CC-BY 4.0

#include "Hashset.hpp"

Hashset::Hashset() {
  hashset = {};
  algorithmName = "Hashset";
}

size_t Hashset::insert(int64_t element) {
  hashset.emplace(element);
  return 1;
}

size_t Hashset::search(int64_t element) {
  hashset.find(element);
  return 1;
}

size_t Hashset::remove(int64_t element) {
  if (hashset.find(element) != hashset.end()) {
    hashset.erase(element);
    return 1;
  } 
  return 0;
}

size_t Hashset::getElementCount() {
  return this->hashset.size();
}

