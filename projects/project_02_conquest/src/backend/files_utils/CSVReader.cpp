// Copyright 2025 stack_underflow CC-BY 4.0

#include "CSVReader.hpp"

void CSVReader::openFile(const char *fileName) {
  if (!fileName) throw NullFilenameException();
  if (!this->isCSV(fileName)) throw NotCSVException(fileName);

  this->CSVFile = fopen(fileName, "r");
  if (!this->CSVFile) throw OpenFileException(fileName);
}


bool CSVReader::isCSV(const char* fileName) {
  if (!fileName) throw NullFilenameException();

  // Returns position of the last period, to find extension start
  const char* extension = strrchr(fileName, '.');
  if (!extension) return false;

  // Case-insensitive compare to ".csv"
  return strcasecmp(extension, ".csv") == 0;
}


void CSVReader::skipLine() {
  if (this->CSVFile) {
    // *[^\n] indicates to not store anything except new line anywhere.
    fscanf(this->CSVFile, "%*[^\n]\n");
  }
}


void CSVReader::decomposeLines(const char* fileName,
    std::vector<std::vector<std::string>>& csvData, bool skipHeader) {
  // If file not open, open file
  if (!this->CSVFile) this->openFile(fileName);

  // Buffer to temporarily store line
  char buffer[MAX_SIZE_BUFFER];
  // Skip first line if header is to be skipped
  if (skipHeader) {
    this->skipLine();
  }
  // While not reached end of file
  while (fgets(buffer, sizeof(buffer), this->CSVFile)) {
    // Vector to store words in the line
    std::vector<std::string> line;
    // Separate the read line in buffer into tokens using comma as delimitator
    char* token = std::strtok(buffer, ",");  // Gets first token

    while (token != nullptr) {
      if (strlen(token) > 0) {
        line.push_back(std::string(token));
      } else {
        break;  // Break when empty element is found
      }
      // Using nullptr means "read where you last left off"
      token = std::strtok(nullptr, ",");  // Gets next token
    }

    // Add line to separated collection
    csvData.push_back(line);
  }
}


void CSVReader::closeFile() {
  if (this->CSVFile) {
    fclose(CSVFile);
  }
}
