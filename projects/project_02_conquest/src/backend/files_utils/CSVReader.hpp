// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>

#include "CSVExceptions.hpp"

#define MAX_SIZE_BUFFER 1024

class CSVReader {
 protected:
  FILE* CSVFile = nullptr;

 private:
  /// @brief Determines if extension of file name is csv or CSV.
  /// @param fileName File name to evaluate.
  /// @return true if file has .csv extension
  bool isCSV(const char* fileName);

 public:
  // Constructor
  CSVReader() = default;
  // Destructor
  ~CSVReader() = default;

  /**
   * @brief Opens a CSV file for reading.
   *
   * @param fileName Path to the CSV file.
   *
   * @throws NullFilenameException if the filename is null.
   * @throws NotCSVException if the file does not have a .csv extension.
   * @throws OpenFileException if the file cannot be opened.
   */
  void openFile(const char* fileName);

  /// @brief Skip a line in the CSV file if open.
  void skipLine();
  /**
   * @brief Reads and tokenizes the lines of a CSV file.
   *
   * If the file is not already open, it attempts to open it.
   * Parsed data is returned in a 2D vector structure.
   *
   * @param fileName Path to the CSV file.
   * @param csvData Reference to a vector where parsed data will be stored.
   *
   * @throws NullFilenameException if the filename is null.
   * @throws NotCSVException if the file does not have a .csv extension.
   * @throws OpenFileException if the file cannot be opened.
  */
  void decomposeLines(const char* fileName
      , std::vector<std::vector<std::string>>& csvData);

  /// @brief Closes file if open.
  void closeFile();
};
