// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#define PROBE_COST 10

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "ActionLog.hpp"
#include "SpaceVessel.hpp"

/// @brief Attacking type vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class AttackVessel : public SpaceVessel {
 protected:
  /// vessel algorithm
  AttackAlgorithm<DataType, WeightType>* attackAlgorithm;

 public:
  /// Constructor
  AttackVessel() : SpaceVessel(PROBE_COST) {
  }
  // TODO(any): DISABLE_COPY macro
  /// Destructor
  ~AttackVessel() {
    delete this->attackAlgorithm;
    this->attackAlgorithm = nullptr;
  }

  /**
   * @brief Locate new elements and add them the corresponding container
   * 
   * @param startNode first element to visit
   * @param endNode Goal node
   * @param adjacencyList read only map with available edges from each node
   * @param totalWeight total weight of the attack
   * @return ActionLog containing algorithm iteratations and time
   */
  virtual ActionLog probe(Node<DataType>* startNode, Node<DataType>* endNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , size_t& totalWeight) {
    // record algorithm execution
    ActionLog actionLog = ActionLog(this->attackAlgorithm->getName());
    // timed algorithm execution
    actionLog.recordStart();
    size_t iterations = attackAlgorithm->attack(startNode, endNode
        adjacencyList, totalWeight);
    actionLog.recordEnd(iterations);
    return actionLog;
  }
};
