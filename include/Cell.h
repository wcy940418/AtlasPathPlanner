#include "Util.h"

#ifndef _LIBCPP_ROBOT_CELL
#define _LIBCPP_ROBOT_CELL

#define ROB_EMPTY 0
#define	ROB_STONE 1
#define	ROB_START 2
#define ROB_DEST 3

/**
Cell of Robot in the graph
*/
class Cell {
public:

	int x, y, dir;

	Cell();

	Cell(int x, int y, int dir);

	bool operator < (const Cell& cell) const;

};

#endif
