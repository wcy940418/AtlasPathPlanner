#include "Util.h"
#include "Graph.h"
#include "Cell.h"
#include <opencv2/opencv.hpp>

Graph::Graph() {

}
	
Graph::Graph(int row, int col) {
	Init(row, col);
}

Graph::Graph(cv::Mat img) {
	Init(img.rows, img.cols);

	for (int i = 0 ; i < row; i++) {
			for (int j = 0; j < col; j++) {
					int color = (int)img.at<uchar>(i, j);
					if (color != 255) {
						Set(i + 1, j + 1, ROB_STONE);
					} else {
						Set(i + 1, j + 1, ROB_EMPTY);
					}
			}
	}
}	

void Graph::Init(int row, int col) {
	this->row = row, this->col = col;
	G.resize(row + 1, std::vector<int> (col + 1));
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			G[i][j] = ROB_EMPTY;
		}
	}
}

void Graph::Set(int x, int y, int status) {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	G[x][y] = status;
}

int Graph::Get(int x, int y) const {
	assert (x >= 1 && x <= row && y >= 1 && y <= col);
	return G[x][y];
}

bool Graph::canGo(int x, int y) const {
	if (x >= 1 && x <= row && y >= 1 && y <= col) {
		return G[x][y] != ROB_STONE; 
	} else {
		return false;
	}
}

cv::Mat Graph::show(std::vector<Cell> path) const {
	cv::Mat img(row, col, 0);
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			img.at<uchar>(i - 1, j - 1) = (G[i][j] == ROB_STONE ? 0 : 255);
		}
	}
	for (int i = 0; i < (int)path.size(); i++) {
			Cell cur = path[i];
			int x = cur.x, y = cur.y, dir = cur.dir;
			img.at<uchar>(x - 1, y - 1) = 0;
	}
	return img;
}