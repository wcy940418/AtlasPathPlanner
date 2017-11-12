#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <set>
#include <map>
#include <queue>
using namespace std;

using State = pair<pair<int,int>,int>;

class PathPlanner {
public: 
  void SetDestination(int x, int y) {
      destX = x;
      destY = y;
  }
  void SetStart(int x, int y) {
      startX = x;
      startY = y;
  }
  
  PathPlanner(int row = 10, int col = 10) {
      GraphInit(row, col);
  }

  void GraphInit(int row, int col) {
      this->row = row;
      this->col = col;
      assert(row > 0 && col > 0);
      graph.resize(row + 1, vector<int>(col + 1, 0));
      stepWeight = directionWeight = 1;
  }

  void SetStepAndDirectionWeight(int stepWeight, int directionWeight) {
      this->stepWeight = stepWeight;
      this->directionWeight = directionWeight;
  }

  void SetBarrier(int x, int y) {
      assert(x > 0 && x <= row && y > 0 && y <= col);
      graph[x][y] = 1;
  }

  void SetEmpty(int x, int y) {
      assert(x > 0 && x <= row && y > 0 && y <= col);
      graph[x][y] = 0;
  }

  // use SPFA Algorithm as path planning
  vector<State> PathPlanning() {
      vector<vector<vector<int> > > dis(4, vector<vector<int> >(row + 1, vector<int>(col + 1, INT_MAX)));
      map<State, int> vis;
      map<State, State> pre;
      queue<State> que;
      for (int i = 0; i < 4; i++) {
          int dx = startX + dir[i][0];
          int dy = startY + dir[i][1];
          if (!IsValid(dx, dy)) continue;
          State state = {{dx, dy}, i};
          pre[state] = {{startX, startY}, -1};
          vis[state] = 1;
          que.push(state);
          dis[i][dx][dy] = 0;
      }
      while (!que.empty()) {
          State cur = que.front();
          que.pop();
          vis[cur] = 0;
          int x = cur.first.first, y = cur.first.second, d = cur.second;
          if (x == destX && y == destY) continue;
          for (int i = 0; i < 4; i++) {
              int dx = x + dir[i][0];
              int dy = y + dir[i][1];
              if (!IsValid(dx, dy)) continue;

              int cost = dis[d][x][y] + stepWeight + (i == d ? 0 : directionWeight);

              if (cost < dis[i][dx][dy]) {
                  dis[i][dx][dy] = cost;
                  State next = {{dx, dy}, i}; 
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
              now = {{destX, destY}, i};
          }
      }
      paths.clear();
      if (res == INT_MAX) {
          cout << "can not find the path!" << endl;
      } else {
          cout << "find a path, cost is " << res << endl;
          while (now.second != -1) {
            paths.push_back(now);
            now = pre[now];
          }
          reverse(paths.begin(), paths.end());
      }
      return paths;
  }
  void ShowGraph(bool path = false) {
      if (path) {
          for (auto p : paths) {
              graph[p.first.first][p.first.second] = 2;
          }
      } else {
      }

      for (int i = 1; i <= row; i++) {
          for (int j = 1; j <= col; j++) {
              if (i == startX && j == startY) {
                  cout << "S";
              } else if (i == destX && j == destY) {
                  cout << "D";
              } else {
                  if (graph[i][j] == 0) cout << ".";
                  else if (graph[i][j] == 1) cout << '#';
                  else if (graph[i][j] == 2) cout << '*';
                  else cout << graph[i][j];
              }
          }
          cout << endl;
      }
      if (path) {
          for (auto p : paths) {
              graph[p.first.first][p.first.second] = 0;
          }
      }
      cout << endl << endl;
  }
private:
  int row, col;
  vector<State> paths;
  vector<vector<int> > graph;
  int startX, startY, destX, destY;
  int stepWeight, directionWeight;
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  string dirName[4] = {"North", "East", "South", "West"};
  bool IsValid(int x, int y ) {
      return x > 0 && x <= row && y > 0 && y <= col && graph[x][y] == 0;
  }
};

