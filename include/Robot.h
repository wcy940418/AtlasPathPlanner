#ifndef _LIBCPP_ROBOT_ROBOT
#define _LIBCPP_ROBOT_ROBOT

#include "Graph.h"
#include "PathPlanner.h"
#include <vector>
#include "Cell.h"

namespace robot {

  class Robot {
  private:
    PathPlanner plan;

  public: 

    Cell start, dest;

    std::vector<Cell> path;

    Graph real, know;

    Robot();

    void SetGraph(const Graph& graph);

    void SetPathPlanner(const PathPlanner& plan);

    void SetStart(Cell start);

    void SetDest(Cell dest);

    bool GoNext(Cell cell);

    bool Go();

    void GoBack(int step);

    void SetStone(int x, int y, int radius);

  };

}

#endif