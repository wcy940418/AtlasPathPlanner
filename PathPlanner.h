#ifndef _LIBCPP_PATH_PLANNER
#define _LIBCPP_PATH_PLANNER

#include <string>
#include <vector>
using namespace std;

// using State = pair<pair<int,int>,int>;
class State {
public:
  int x, y;
  int dir;
  State();
  State(int x, int y, int dir);
  bool operator < (const State& state) const;
};

class PathPlanner {
public: 
  void SetDestination(int x, int y);
  void SetStart(int x, int y, int dir);
  PathPlanner(int row, int col);

  void GraphInit(int row, int col);

  void SetStepAndDirectionWeight(int stepWeight, int directionWeight);

  void SetBarrier(int x, int y);

  void SetEmpty(int x, int y);

  // use SPFA Algorithm as path planning
  vector<State> PathPlanning();
  // void ShowGraph(bool path = false);
private:
  int row, col;
  // vector<State> paths;
  vector<vector<int> > graph;
  int startX, startY, destX, destY, startDir;
  int stepWeight, directionWeight;

  // define four directions
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  string dirName[4] = {"North", "East", "South", "West"};

  // check if it is a empty position
  bool IsValid(int x, int y);
};

#endif