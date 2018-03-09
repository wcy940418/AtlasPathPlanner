#ifndef _LIBCPP_ROBOT_PATH_PLANNER
#define _LIBCPP_ROBOT_PATH_PLANNER

#include "Graph.h"
#include "Cell.h"

namespace robot {

  class PathPlanner {

  private:

    int stepWeight, directionWeight;

  public: 

    PathPlanner();

    void SetStepAndDirectionWeight(int stepWeight, int directionWeight);

    /** use SPFA Algorithm as path planning */
    std::vector<Cell> PathPlanning(const Graph& graph, const Cell start, const Cell dest);

  };

}

#endif