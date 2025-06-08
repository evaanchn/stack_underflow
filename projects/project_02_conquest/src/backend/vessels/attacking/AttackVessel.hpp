// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "DamageLog.hpp"
#include "SpaceVessel.hpp"

#define ATTACK_COST 5  ///< Cost of an attack vessel

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
  AttackVessel() : SpaceVessel(ATTACK_COST) {
  }
  // TODO(any): DISABLE_COPY macro
  /// Destructor
  ~AttackVessel() {
    delete this->attackAlgorithm;
    this->attackAlgorithm = nullptr;
  }

  /**
   * @brief Calculates the attack path from startNode to endNode getting the
   * acuumulated weight
   * @param startNode first element to visit
   * @param endNode Goal node
   * @param adjacencyList read only map with available edges from each node
   * @param nodeIndexes Map nodes to their assigned index
   * @param validEdges matrix to check if an edge is accesible
   * @param totalWeight total weight of the attack
   * @return DamageLog containing execution iteratations, time and damage
   */
  virtual DamageLog attack(Node<DataType>* startNode, Node<DataType>* endNode
      , const std::unordered_map<Node<DataType>*
        , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
      , std::unordered_map<Node<DataType>*, size_t>& nodeIndexes
      , std::vector<std::vector<bool>>& validEdges
      , WeightType& totalWeight) {
    // record algorithm execution
    DamageLog damageLog = DamageLog(this->attackAlgorithm->getName());
    damageLog.setResponsible("AttackVessel");
    // timed algorithm execution
    damageLog.recordStart();
    size_t iterations = attackAlgorithm->attack(startNode, endNode
      , adjacencyList, nodeIndexes, validEdges, totalWeight);
    damageLog.recordEnd(iterations);
    // set damage amount
    damageLog.setDamage(totalWeight);
    return damageLog;
  }
};
