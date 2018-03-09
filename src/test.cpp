#include <iostream>
#include "PathPlanner.h"
#include "Graph.h"
#include "Cell.h"
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("../asset/graph03.jpg", 0);
    // imshow("image",img);
    // waitKey(33);
		// return 0;
    int row = img.rows;
    int col = img.cols;
    printf("row : %d , col : %d\n", row, col);

		robot::Graph graph(img);
		std::cout << graph.row << " " << graph.col << std::endl;
		robot::Cell start(robot::Cell(30, 30, 1));
		robot::Cell dest(robot::Cell(400, 30, 1));

    robot::PathPlanner planner;
		planner.SetStepAndDirectionWeight(1, 500);

		// for (int i = 1; i <= row; i++) {
		// 	for (int j = 1; j <= col; j++) {
		// 		cout << graph.Get(i, j);
		// 	}
		// 	cout << endl;
		// }
    // for (int i = 0 ; i < row; i++) {
    //     for (int j = 0; j < col; j++) {
    //         int color = (int)img.at<uchar>(i, j);
    //         if (color != 255) {
    //             p.SetBarrier(i + 1, j + 1);
    //         } else {
    //             p.SetEmpty(i + 1, j + 1);
    //         }
    //     }
    // }
    // p.SetStepAndDirectionWeight(1, 100);
    std::vector<robot::Cell> path = planner.PathPlanning(graph, start, dest);
    // p.ShowGraph(true);
    // for (int i = 0; i < paths.size(); i++) {
    //     Cell cur = paths[i];
    //     int x = cur.x;
    //     int y = cur.y;
    //     int dir = cur.dir;
    //     // cout << x << " " << y << endl;
    //     img.at<uchar>(x - 1, y - 1) = 0;
    // }

		std::cout << "show images" << std::endl;
    cv::imshow("image", graph.show(path));
    cv::waitKey();

    return 0;
}
