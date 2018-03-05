#ifndef _LIBCPP_ROBOT_ROBOT
#define _LIBCPP_ROBOT_ROBOT

#include "Util.h"

#include "Graph.h"
#include "PathPlanner.h"
#include "Robot.h"

using namespace std;

class Robot {
public: 
	Cell start, dest;

	Graph real, know;

	Robot();

	void SetGraph(const Graph& graph);

	void SetStart(Cell start);

	void SetDest(Cell dest);

};

#endif