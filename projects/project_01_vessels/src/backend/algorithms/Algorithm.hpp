// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

class algorithm {
 public:
    /// @brief constructor method of the algorithm class
    algorithm();

    /**
     @brief assigned method for inserting elements
     @param element element to insert
     @return the number of iterations made for the insertion process
    */
    size_t insert(int64_t element);

    /**
     @brief method assigned to search for elements
     @see insert
    */
    size_t search(int64_t element);

    /**
     @brief method assigned for removing elements
     @see insert
    */
    size_t remove(int64_t element);

    /// @brief gets the name of the initialized algorithm
    std::string getAlgorithmName();

    /// @brief gets the value of the element_count parameter
    std::size_t getElementCount();

    /// @brief increments the value of the element_count attribute once
    void increaseElementCount();

    /**
     @brief assigns the name of the created algorithm to the algorithm_name 
       attribute
     @param _algorithmName name to assign
    */
    void setAlgorithmName(std::string _algorithmName);

 private:
    std::string algorithmName;
    size_t elementCount;
    std::unordered_set<int64_t> elementRecord;
};
