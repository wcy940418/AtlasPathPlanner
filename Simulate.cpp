#include <iostream>
#include <string>
#include "PathPlanner.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void simulate(string pic, int startX, int startY, int startDir, int destX, int destY) {
    // imshow("image",img);
    Mat img = imread("../" + pic, 0);
    int row = img.rows;
    int col = img.cols;
    printf("row : %d , col : %d\n", row, col);

    PathPlanner robot(row, col);
    robot.SetDestination(destX, destY);
    robot.SetStepAndDirectionWeight(1, 1);

    PathPlanner realWorld(row, col);

    for (int i = 0 ; i < row; i++) {
        for (int j = 0; j < col; j++) {
            robot.SetEmpty(i + 1, j + 1);
            int color = (int)img.at<uchar>(i, j);
            if (color == 0) {
                realWorld.SetBarrier(i + 1, j + 1);
                // img.at<uchar>(i, j) = 0;
            } else {
                realWorld.SetEmpty(i + 1, j + 1);
            }
        }
    }

    // imshow("image", img); waitKey(0);

    int curX = startX, curY = startY, curDir = startDir;
    // Mat origin = img;
    // for (int i = 0; i < row; i++) {
    //   for (int j = 0; j < col; j++) {
    //     origin.at<uchar>(j - 1, j - 1) = 255;
    //   }
    // }
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        img.at<uchar>(i, j) = 255;
      }
    }
    while (curX != destX || curY != destY) {
      cout << "new path!!" << endl;
      robot.SetStart(curX, curY, curDir);
      vector<State> paths = robot.PathPlanning();
      // Mat findPath = origin;
      int setLine = 0;
      // Mat tmp = img;
      for (State state : paths) {
        int x = state.x, y = state.y, dir = state.dir;
        setLine++;
        img.at<uchar>(x - 1, y - 1) = ((setLine % 10 < 5) ? 255 : 0);
      }

      for (State state : paths) {
          imshow("image", img);
          waitKey(33);
          int x = state.x, y = state.y, dir = state.dir;
          if (realWorld.IsValid(x, y)) {
            curX = x, curY = y, curDir = dir;
            // findPath.at<uchar>(x - 1, y - 1) = 0;
            img.at<uchar>(x - 1, y - 1) = 0;
            // tmp.at<uchar>(x - 1, y - 1) = 0;
          } else {
            // for (int i = -1; i <= 1; i++) {
            //   for (int j = -1; j <= 1; j++) {
            //     if (i + x > 0 && i + x <= row && j + y > 0 && j + y <= col) {
            cout << "find barrier " <<  x << "," << y << endl;
            robot.SetBarrier(x, y);
            img.at<uchar>(x - 1, y - 1) = 0;
            // img.at<uchar>(x - 1, y - 1) = 0;
            //   }
            // }
            // }
            break;
          }
      }
    }
}

int main() {
    simulate("graph01.jpg", 200, 50, 0, 400, 50);
    return 0;
}
