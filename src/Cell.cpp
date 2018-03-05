#include "Util.h"
#include "Cell.h"

Cell::Cell() {

}

Cell::Cell(int x, int y, int dir): x(x), y(y), dir(dir) {

}

bool Cell::operator < (const Cell& cell) const {
	if (x != cell.x) return x < cell.x;
	if (y != cell.y) return y < cell.y;
	return dir < cell.dir;
}