// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <unordered_set>

struct Node {
  size_t value;
  Node* left_child;
  Node* right_child;
};

class algorithm {
 public:
    /// @brief método constructor de la clase algorithm
    algorithm();

    /**
     @brief método asignado para la inserción de elementos
     @param element elemento a insertar
     @return la cantidad de iteraciones hechas para el proceso de inserción
    */
    int insert(size_t element);

    /**
     @brief método asignado para la bùsqueda de elementos
     @see insert
    */
    int search(size_t element);

    /**
     @brief método asignado para la eliminación de elementos
     @see insert
    */
    int remove(size_t element);

    /// @brief obtiene el nombre del algoritmo inicializado
    std::string get_algorithm_name();

    /// @brief obtiene el valor del parámetro element_count
    std::size_t get_element_count();

    /// @brief incrementa una vez el valor del atributo element_count
    void increase_element_count();

    /**
     @brief aigna el nombre del algoritmo creado en el atributo algorithm_name
     @param _algorithm_name nombre a asignar
    */
    void set_algorithm_name(std::string _algorithm_name);

 private:
    std::string algorithm_name;
    size_t element_count;
    std::unordered_set<size_t> element_record;
};
