#include "Util.h"
#include "PathPlanner.h"
using namespace std;

void PathPlanner::SetStepAndDirectionWeight(int stepWeight, int directionWeight) {
  // this->stepWeight = stepWeight;
  // this->directionWeight = directionWeight;
}

// use SPFA Algorithm as path planning
vector<State> PathPlanner::PathPlanning(const Graph& graph) {
  // vector<vector<vector<int> > > dis(4, vector<vector<int> >(row + 1, vector<int>(col + 1, INT_MAX)));
  // map<State, int> vis;
  // map<State, State> pre;
  // queue<State> que;
  // State startState(startX, startY, startDir);
  // vis[startState] = 1;
  // dis[startDir][startX][startY] = 0;
  // que.push(startState);
  // while (!que.empty()) {
  //     State cur = que.front();
  //     que.pop();
  //     vis[cur] = 0;
  //     int x = cur.x, y = cur.y, d = cur.dir;
  //     if (x == destX && y == destY) continue;
  //     for (int i = 0; i < 4; i++) {
  //         int dx = x + dir[i][0];
  //         int dy = y + dir[i][1];
  //         if (!IsValid(dx, dy)) continue;

  //         int cost = dis[d][x][y] + stepWeight + (i == d ? 0 : directionWeight);

  //         if (cost < dis[i][dx][dy]) {
  //             dis[i][dx][dy] = cost;
  //             State next(dx, dy, i);
  //             pre[next] = cur;
  //             if (vis[next] == 0) {
  //                 vis[next] = 1;
  //                 que.push(next);
  //             }
  //         }
  //     }
  // }
  // int res = INT_MAX;
  // State now;
  // for (int i = 0; i < 4; i++) {
  //     if (res > dis[i][destX][destY]) {
  //         res = dis[i][destX][destY];
  //         now = State(destX, destY, i);
  //         // now = {{destX, destY}, i};
  //     }
  // }
  // vector<State> paths;
  // if (res == INT_MAX) {
  //     cout << "can not find the path!" << endl;
  // } else {
  //     cout << "find a path, cost is " << res << endl;
  //     do {
  //       paths.push_back(now);
  //       now = pre[now];
  //     } while (now.x != startX || now.y != startY);
  //     reverse(paths.begin(), paths.end());
  // }
  // return paths;
}