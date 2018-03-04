#include "Util.h"
#include "Graph.h"
using namespace std;

Graph::Graph() {

}
	
Graph::Graph(int row, int col) {
	Init(row, col);
}
	
void Graph::Init(int row, int col) {
	G.resize(row + 1, vector<int> (col + 1, EMPTY));
}

void Graph::SetDest(int x, int y) {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	G[x][y] = DEST;
}

void Graph::SetStart(int x, int y) {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	G[x][y] = START;
}

void Graph::SetStone(int x, int y) {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	G[x][y] = STONE;
}

void Graph::SetEmpty(int x, int y) {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	G[x][y] = EMPTY;
}