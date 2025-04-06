// Copyright 2025 stack_underflow CC-BY 4.0

#include "algorithm.hpp"

algorithm::algorithm() {
  element_count = 0;
}

std::string algorithm::get_algorithm_name() {
  return algorithm_name;
}

size_t algorithm::get_element_count() {
  return element_count;
}

void algorithm::increase_element_count() {
  ++element_count;
}

void algorithm::set_algorithm_name(std::string _algorithm_name) {
  algorithm_name = _algorithm_name;
}
