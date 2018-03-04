#ifndef _LIBCPP_ROBOT_PATH_PLANNER
#define _LIBCPP_ROBOT_PATH_PLANNER

#include "Util.h"
#include "Graph.h"
#include "PathPlanner.h"
#include "State.h"

using namespace std;

class PathPlanner {
private:

  int stepWeight, directionWeight;

  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  string dirName[4] = {"North", "East", "South", "West"};

public: 

  void SetStepAndDirectionWeight(int stepWeight, int directionWeight);

  vector<State> PathPlanning(const Graph& graph);

};

#endif