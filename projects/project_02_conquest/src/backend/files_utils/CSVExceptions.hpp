// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <stdexcept>
#include <string>

/* USAGE:
  try {
    // Invocation of method
  } catch (const CSVException& e) {
    std::cerr << "CSV error: " << e.what() << std::endl;
  }
*/

/// @brief Custom exception for CSV file management
class CSVException : public std::runtime_error {
 public:
  // Inherit constructors from std::runtime_error
  // to allow passing error messages
  using std::runtime_error::runtime_error;
};

class NullFilenameException : public CSVException {
 public:
  NullFilenameException() : CSVException("Filename is null") {}
};

class NotCSVException : public CSVException {
 public:
  explicit NotCSVException(const std::string& filename)
    : CSVException("File: " + filename + " is not a CSV") {}
};

class OpenFileException : public CSVException {
 public:
  explicit OpenFileException(const std::string& filename)
    : CSVException("Failed to open file: " + filename) {}
};
