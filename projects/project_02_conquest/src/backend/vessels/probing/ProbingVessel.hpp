// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// #include "GameConstants.hpp"
#include "ActionLog.hpp"
#include "SpaceVessel.hpp"

// TODO(any): Add game constants header
#define PROBE_COST 3

/// @brief Probing type vessel
/// @tparam DataType planets type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class ProbingVessel : public SpaceVessel {
 protected:
  /// vessel algorithm
  TraversalAlgorithm<DataType, WeightType>* traversalAlgorithm;

 public:
  /// Constructor
  ProbingVessel() : SpaceVessel(PROBE_COST) {
  }
  // TODO(any): DISABLE_COPY macro
  /// Destructor
  ~ProbingVessel() {
    delete this->traversalAlgorithm;
    this->traversalAlgorithm = nullptr;
  }

  /**
   * @brief Locate new elements and add them the corresponding container
   * 
   * @param startingNode starting point
   * @param adjacencyList read only map with available edges from each node
   * @param exploredElements explored planets elements container
   * @param limit exploration limit
   * @return ActionLog containing algorithm iteratations and time
   */
  virtual ActionLog probe(Node<DataType>* startingNode
    , const std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
    , std::unordered_set<DataType>& exploredElements, const WeightType limit) {
    // record algorithm execution
    ActionLog actionLog = ActionLog(this->traversalAlgorithm->getName());
    actionLog.setResponsible("ProbingVessel");
    // whenever the graph is not fully explored and starting node
    // is already explored, execute the algorithm
    if (exploredElements.find(startingNode->getData())
      != exploredElements.end()) {
      // timed algorithm execution
      actionLog.recordStart();
      size_t iterations = traversalAlgorithm->traverse(startingNode,
         adjacencyList, exploredElements, limit);
      actionLog.recordEnd(iterations);
    }
    return actionLog;
  }
};
