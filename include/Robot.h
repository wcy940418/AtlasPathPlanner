#ifndef _LIBCPP_ROBOT_ROBOT
#define _LIBCPP_ROBOT_ROBOT

#include "Graph.h"
#include "PathPlanner.h"

namespace robot {

  class Robot {

  public: 

    Cell start, dest;

    Graph real, know;

    Robot();

    void SetGraph(const Graph& graph);

    void SetStart(Cell start);

    void SetDest(Cell dest);

  };

}

#endif