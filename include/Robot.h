#ifndef _LIBCPP_ROBOT_ROBOT
#define _LIBCPP_ROBOT_ROBOT

#include "Util.h"

#include "Graph.h"
#include "PathPlanner.h"
#include "Robot.h"

using namespace std;

class Robot {
public: 

	Graph real, know;

	Robot();

};

#endif