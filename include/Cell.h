#ifndef _LIBCPP_ROBOT_CELL
#define _LIBCPP_ROBOT_CELL


namespace robot {

  /** Cell of Robot in the graph */
  class Cell {

  public:

    int x, y, dir;

    Cell();

    Cell(int x, int y, int dir);

    bool operator < (const Cell& cell) const;

  };

}

#endif
