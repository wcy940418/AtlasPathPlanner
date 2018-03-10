#ifndef _LIBCPP_ROBOT_GRAPH
#define _LIBCPP_ROBOT_GRAPH

#include "Cell.h"
#include <opencv2/opencv.hpp>
#include <vector>

namespace robot {

  /** grid status in the graph */
  #define ROB_EMPTY 0
  #define	ROB_STONE 1
  #define	ROB_START 2
  #define ROB_DEST 3

  #define BLACK 0
  #define WHITE 255

  class Graph {

  private:

    std::vector<std::vector<int>> G;

  public:

    int row, col;

    Graph();

    Graph(cv::Mat img);

    Graph(int row, int col);

    /** initially all cells in graph is empty */
    void Init(int row, int col);

    void Set(int x, int y, int status);

    int Get(int x, int y) const;

    bool canGo(int x, int y) const;

    cv::Mat show(std::vector<Cell> path) const;

  };

}
#endif

