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
  void PathPlanning() {
      vector<vector<vector<int>>> dis(4, vector<vector<int>>(row + 1, vector<int>(col + 1, INT_MAX)));
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
      if (res == INT_MAX) {
          cout << "can not find the path!" << endl;
      } else {
          cout << "find a path, cost is " << res << endl;
          paths.clear();
          while (now.second != -1) {
            paths.push_back(now);
            now = pre[now];
          }
          reverse(paths.begin(), paths.end());
      }
  }
  void showGraph(bool path = false) {
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
  vector<vector<int>> graph;
  int startX, startY, destX, destY;
  int stepWeight, directionWeight;
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  string dirName[4] = {"North", "East", "South", "West"};
  bool IsValid(int x, int y ) {
      return x > 0 && x <= row && y > 0 && y <= col && graph[x][y] == 0;
  }
};
class Test {
public:
    void case1() {
        cout << "case 1 : row: " << 5 << " col: " << 5 << endl;
        PathPlanner plan(5, 5);
        plan.SetStart(1, 1);
        plan.SetDestination(5, 5);
        plan.SetBarrier(3, 1);
        plan.SetBarrier(1, 5);
        plan.SetBarrier(2, 5);
        plan.showGraph();
        plan.PathPlanning();
        plan.showGraph(true);
        cout << endl;
    }


    void case2() {
        cout << "case 2 : row: " << 10 << " col: " << 10 << endl;
        PathPlanner plan(10, 10);
        plan.SetStart(1, 1);
        plan.SetDestination(10, 1);
        plan.SetBarrier(2, 1);
        for (int i = 2; i < 10; i++) {
            plan.SetBarrier(i, i);
        }
        plan.showGraph();
        plan.PathPlanning();
        plan.showGraph(true);
        cout << endl;
    }

    void case3() {
        cout << "case 3 : row: " << 10 << " col: " << 10 << endl;
        PathPlanner plan(10, 10);
        for (int i = 2; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                plan.SetBarrier(i, j);
            }
        }
        for (int i = 2; i <=6; i++) {
            plan.SetEmpty(i, 1);
        }
        for (int i = 1; i <= 9; i++) {
            plan.SetEmpty(6, i);
        }
        for (int i = 7; i <= 9; i++) {
            plan.SetEmpty(i, 5);
        }
        plan.SetStart(1, 1);
        plan.SetDestination(10, 1);
        cout << "set step weight " << 1 << 
            ", set directionWeight " << 100 << endl;
        plan.SetStepAndDirectionWeight(1, 100);
        plan.showGraph();
        plan.PathPlanning();
        plan.showGraph(true);
        cout << endl;
    }
};
int main () {
    cout << "Graph: S means start, D means destination, . means empty block, # means barrier, * means the suggested path" << endl << endl;
    Test test;
    test.case1();
    test.case2();
    test.case3();

    return 0;
}


