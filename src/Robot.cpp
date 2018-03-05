#include "Util.h"
#include "Robot.h"

using namespace std;

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
