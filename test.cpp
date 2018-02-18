#include <iostream>
#include "PathPlanner.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main() {
    Mat img = imread("../graph01.jpg", 0);
    // imshow("image",img);
    int row = img.rows;
    int col = img.cols;
    printf("row : %d , col : %d\n", row, col);
    PathPlanner p(row, col);
    p.SetStart(250, 10, 0);
    p.SetDestination(250, 300);
    for (int i = 0 ; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int color = (int)img.at<uchar>(i, j);
            if (color != 255) {
                p.SetBarrier(i + 1, j + 1);
            } else {
                p.SetEmpty(i + 1, j + 1);
            }
        }
    }
    p.SetStepAndDirectionWeight(1, 100);
    vector<State> paths = p.PathPlanning();
    // p.ShowGraph(true);
    for (int i = 0; i < paths.size(); i++) {
        State cur = paths[i];
        int x = cur.x;
        int y = cur.y;
        int dir = cur.dir;
        // cout << x << " " << y << endl;
        img.at<uchar>(x - 1, y - 1) = 0;
    }

    imshow("image",img);
    waitKey(0);

    return 0;
}
