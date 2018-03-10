#include "Robot.h"

namespace robot {

  Robot::Robot() {

  }

  void Robot::SetGraph(const Graph& graph) {
    real = graph;
    know.Init(real.row, real.col);
  }

  void Robot::SetPathPlanner(const PathPlanner& plan) {
    this->plan = plan;
  }
  
  void Robot::SetStart(Cell start) {
    this->start = start;
  }

  void Robot::SetDest(Cell dest) {
    this->dest = dest;
  }

  bool Robot::GoNext(Cell cell) {
    if (!real.canGo(cell.x ,cell.y)) {
      SetStone(cell.x, cell.y, 20);
      GoBack(25);
      return false;
    }
    path.push_back(cell);
    start = cell;
    cv::imshow("test", real.show(path));
    cv::waitKey(33);
    return true;
  }

  bool Robot::Go() {
    Cell firstCell = path.empty() ? start : path.back();
    std::vector<Cell> findPath = plan.PathPlanning(know, firstCell, dest);
    // cv::waitKey(200);
    for (int i = 1; i < (int)findPath.size(); i++) {
      Cell next = findPath[i];
      if (!GoNext(next)) break;
    }
    if (!path.empty() && (path.back().x == dest.x && path.back().y == dest.y)) return true;
    else return false;
  }

  void Robot::GoBack(int step) {
    int goBackStep = std::min(step, (int)path.size() - 1);
    for (int i = 0; i < goBackStep; i++) {
      path.pop_back();
    }
  }

  void Robot::SetStone(int x, int y, int radius) {
    for (int i = -radius; i <= radius; i++) {
      for (int j = -radius; j <= radius; j++) {
        int dx = x + i, dy = y + j;
        if (know.canGo(dx, dy)) {
          know.Set(dx, dy, ROB_STONE);
        }
      }
    }
  }

}

