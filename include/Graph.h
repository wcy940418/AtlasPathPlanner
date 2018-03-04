#include "Util.h"

using namespace std;

#ifndef _LIBCPP_ROBOT_GRAPH
#define _LIBCPP_ROBOT_GRAPH

class Graph {
public:
	int row, col;
	vector<vector<int>> G;

	Graph();

	Graph(int row, int col);
	
	void Init(int row, int col);

	void SetDest(int x, int y);

  void SetStart(int x, int y);

  void SetStone(int x, int y);

  void SetEmpty(int x, int y);

	int get(int x, int y);
};

#endif

