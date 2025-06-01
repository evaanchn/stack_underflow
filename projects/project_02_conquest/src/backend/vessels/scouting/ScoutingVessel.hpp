// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// #include "GameConstants.hpp"
#include "ActionLog.hpp"
#include "PathingAlgorithm.hpp"
#include "SpaceVessel.hpp"

// TODO(any): Add game constants header
#define SCOUTE_COST 3

/// @brief Scouting type vessel
/// @tparam DataType elements type
/// @tparam WeightType node edges type
template<typename DataType, typename WeightType>
class ScoutingVessel : public SpaceVessel {
 protected:
  /// vessel algorithm
  PathingAlgorithm<DataType, WeightType>* pathingAlgorithm;

 public:
  /// Constructor
  ScoutingVessel() : SpaceVessel(PROBE_COST) {
  }
  // TODO(any): DISABLE_COPY macro
  /// Destructor
  ~ScoutingVessel() {
    delete this->pathingAlgorithm;
    this->pathingAlgorithm = nullptr;
  }

  /**
   * @brief Scout finding optimal routes to all reachable nodes
   * 
   * @param startingNode starting point
   * @param adjacencyList read only map with available edges from each node
   * @param exploredElements explored planets elements container
   * @param nodeIndexes Map nodes to their assigned index
   * @param measuredEdges matrix to store edges weights obtained from the route
   * @return ActionLog containing algorithm iteratations and time
   */
  virtual ActionLog scout(Node<DataType>* startingNode
    , const std::unordered_map<Node<DataType>*
      , std::unordered_map<Node<DataType>*, WeightType>>& adjacencyList
    , const std::unordered_set<DataType>& exploredElements
    , std::unordered_map<Node<DataType>*, size_t>& nodeIndexes
    , std::vector<std::vector<bool>>& measuredEdges) {
    // record algorithm execution
    ActionLog actionLog = ActionLog(this->pathingAlgorithm->getName());
    // whenever starting node is already explored, execute the algorithm
    if (exploredElements.find(startingNode->getData())
      != exploredElements.end()) {
      // timed algorithm execution
      actionLog.recordStart();
      size_t iterations = pathingAlgorithm->route(startingNode,
         adjacencyList, exploredElements, nodeIndexes, measuredEdges);
      actionLog.recordEnd(iterations);
    }
    return actionLog;
  }
};
