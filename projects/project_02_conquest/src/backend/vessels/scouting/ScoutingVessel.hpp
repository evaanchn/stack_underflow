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
   * @param planetsGraph Graph to work with
   * @param exploredElements explored planets elements container
   * @param measuredEdges matrix to store edges weights obtained from the route
   * @param startingNode starting point
   * @return ActionLog containing algorithm iteratations and time
   */
  virtual ActionLog scout(Graph<DataType, WeightType>* planetsGraph
    , const std::unordered_set<DataType>& exploredElements
    , std::vector<std::vector<bool>>& measuredEdges
    , Node<DataType>* startingNode = nullptr) {
    // record algorithm execution
    ActionLog actionLog = ActionLog(this->pathingAlgorithm->getName());
    actionLog.setResponsible("ScoutingVessel");
    // whenever starting node is already explored, execute the algorithm
    if (exploredElements.find(startingNode->getData())
      != exploredElements.end()) {
      // timed algorithm execution
      actionLog.recordStart();
      size_t iterations = pathingAlgorithm->route(planetsGraph
          , exploredElements, measuredEdges, startingNode);
      actionLog.recordEnd(iterations);
    }
    return actionLog;
  }
};
