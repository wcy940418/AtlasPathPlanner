#include <iostream>
#include "PathPlanner.h"
#include "Graph.h"
#include "Cell.h"
#include <opencv2/opencv.hpp>
#include "Robot.h"

int main() {
    // 07 : (30, 200) to (400, 30)
    // 07 : (30, 30) to (400, 30
    cv::Mat img = cv::imread("../asset/graph08.jpg", 0);

    int row = img.rows;
    int col = img.cols;
    printf("row : %d , col : %d\n", row, col);

		robot::Graph graph(img);
		std::cout << graph.row << " " << graph.col << std::endl;
		robot::Cell start(robot::Cell(30, 30, 1));
		robot::Cell dest(robot::Cell(200, 400, 1));

    robot::PathPlanner planner;
		planner.SetStepAndDirectionWeight(1, 1);

    robot::Robot robot;
    robot.SetStart(start);
    robot.SetDest(dest);
    robot.SetPathPlanner(planner);
    robot.SetGraph(graph);

    while (!robot.Go()) {
      std::cout << "going" << std::endl;
      // cv::imshow("image", robot.real.show(robot.path));
      // cv::waitKey(33);
    }
    cv::waitKey();
    // std::vector<robot::Cell> path = planner.PathPlanning(graph, start, dest);

		// std::cout << "show images" << std::endl;
    // cv::imshow("image", graph.show(path));
    // cv::waitKey();

    return 0;
}
