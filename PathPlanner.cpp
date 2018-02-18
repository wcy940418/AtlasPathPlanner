#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <queue>
#include "PathPlanner.h"
using namespace std;

State::State(){}

State::State(int x, int y, int dir): x(x), y(y), dir(dir){}
bool State::operator < (const State& state) const {
  if (x != state.x) return x < state.x;
  if (y != state.y) return y < state.y;
  return dir < state.dir;
}
void PathPlanner::SetDestination(int x, int y) {
    destX = x;
    destY = y;
}
void PathPlanner::SetStart(int x, int y, int dir) {
    startX = x;
    startY = y;
    startDir = dir;
}
  
PathPlanner::PathPlanner(int row, int col) {
  GraphInit(row, col);
}

void PathPlanner::GraphInit(int row, int col) {
  this->row = row;
  this->col = col;
  assert(row > 0 && col > 0);
  graph.resize(row + 1, vector<int>(col + 1, 0));
  stepWeight = directionWeight = 1;
}

void PathPlanner::SetStepAndDirectionWeight(int stepWeight, int directionWeight) {
  this->stepWeight = stepWeight;
  this->directionWeight = directionWeight;
}

void PathPlanner::SetBarrier(int x, int y) {
  assert(x > 0 && x <= row && y > 0 && y <= col);
  graph[x][y] = 1;
}

void PathPlanner::SetEmpty(int x, int y) {
  assert(x > 0 && x <= row && y > 0 && y <= col);
  graph[x][y] = 0;
}

// use SPFA Algorithm as path planning
vector<State> PathPlanner::PathPlanning() {
  vector<vector<vector<int> > > dis(4, vector<vector<int> >(row + 1, vector<int>(col + 1, INT_MAX)));
  map<State, int> vis;
  map<State, State> pre;
  queue<State> que;
  State startState(startX, startY, startDir);
  vis[startState] = 1;
  dis[startDir][startX][startY] = 0;
  que.push(startState);
  // for (int i = 0; i < 4; i++) {
  //     int dx = startX + dir[i][0];
  //     int dy = startY + dir[i][1];
  //     if (!IsValid(dx, dy)) continue;
  //     State state(dx, dy, i);
  //     pre[state] = State(startX, startY, -1);
  //     // pre[state] = {{startX, startY}, -1};
  //     vis[state] = 1;
  //     que.push(state);
  //     dis[i][dx][dy] = 0;
  // }
  while (!que.empty()) {
      State cur = que.front();
      que.pop();
      vis[cur] = 0;
      int x = cur.x, y = cur.y, d = cur.dir;
      // printf("(%d,%d,%d): %d\n", x, y, dir, dis[d][x][y]);
      if (x == destX && y == destY) continue;
      for (int i = 0; i < 4; i++) {
          int dx = x + dir[i][0];
          int dy = y + dir[i][1];
          if (!IsValid(dx, dy)) continue;

          int cost = dis[d][x][y] + stepWeight + (i == d ? 0 : directionWeight);

          if (cost < dis[i][dx][dy]) {
              dis[i][dx][dy] = cost;
              State next(dx, dy, i);
              pre[next] = cur;
              if (vis[next] == 0) {
                  vis[next] = 1;
                  que.push(next);
              }
          }
      }
  }
  int res = INT_MAX;
  State now;
  for (int i = 0; i < 4; i++) {
      if (res > dis[i][destX][destY]) {
          res = dis[i][destX][destY];
          now = State(destX, destY, i);
          // now = {{destX, destY}, i};
      }
  }
  vector<State> paths;
  if (res == INT_MAX) {
      cout << "can not find the path!" << endl;
  } else {
      cout << "find a path, cost is " << res << endl;
      do {
        paths.push_back(now);
        now = pre[now];
      } while (now.x != startX || now.y != startY);
      reverse(paths.begin(), paths.end());
  }
  return paths;
}
bool PathPlanner::IsValid(int x, int y ) {
  return x > 0 && x <= row && y > 0 && y <= col && graph[x][y] == 0;
}
// void PathPlanner::ShowGraph(bool path = false) {
//   if (path) {
//       for (auto p : paths) {
//           graph[p.first.first][p.first.second] = 2;
//       }
//   } else {
//   }

//   for (int i = 1; i <= row; i++) {
//       for (int j = 1; j <= col; j++) {
//           if (i == startX && j == startY) {
//               cout << "S";
//           } else if (i == destX && j == destY) {
//               cout << "D";
//           } else {
//               if (graph[i][j] == 0) cout << ".";
//               else if (graph[i][j] == 1) cout << '#';
//               else if (graph[i][j] == 2) cout << '*';
//               else cout << graph[i][j];
//           }
//       }
//       cout << endl;
//   }
//   if (path) {
//       for (auto p : paths) {
//           graph[p.first.first][p.first.second] = 0;
//       }
//   }
//   cout << endl << endl;
// }

