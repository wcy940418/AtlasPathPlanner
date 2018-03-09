#include "Robot.h"

namespace robot {

  Robot::Robot() {

  }

  void Robot::SetGraph(const Graph& graph) {
    real = graph;
    know.Init(real.row, real.col);
  }

  void Robot::SetStart(Cell start) {
    this->start = start;
  }

  void Robot::SetDest(Cell dest) {
    this->dest = dest;
  }

}

