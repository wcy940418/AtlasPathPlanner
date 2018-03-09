#include "PathPlanner.h"
#include <queue>
#include <map>
#include <vector>

namespace robot {
  int dir[4][2] = {
    {1, 0}, 
    {0, 1}, 
    {-1, 0}, 
    {0, -1}
  };

  std::string dirName[4] = {
    "North", 
    "East", 
    "South", 
    "West"
  };

  PathPlanner::PathPlanner() {
    SetStepAndDirectionWeight(1, 1);
  }

  void PathPlanner::SetStepAndDirectionWeight(int stepWeight, int directionWeight) {
    this->stepWeight = stepWeight;
    this->directionWeight = directionWeight;
  }

  std::vector<Cell> PathPlanner::PathPlanning(const Graph& graph, const Cell start, const Cell dest) {
    int row = graph.row, col = graph.col;
    std::vector<std::vector<std::vector<int> > > dis(4, std::vector<std::vector<int> >(row + 1, std::vector<int>(col + 1, INT_MAX)));
    std::map<Cell, int> vis;
    std::map<Cell, Cell> pre;
    std::queue<Cell> que;
    vis[start] = 1;
    dis[start.dir][start.x][start.y] = 0;
    que.push(start);
    while (!que.empty()) {
        Cell cur = que.front();
        que.pop();
        vis[cur] = 0;
        int x = cur.x, y = cur.y, d = cur.dir;
        if (x == dest.x && y == dest.y) continue;
        for (int i = 0; i < 4; i++) {
            int dx = x + dir[i][0];
            int dy = y + dir[i][1];
            if (!graph.canGo(dx, dy)) continue;

            int cost = dis[d][x][y] + stepWeight + (i == d ? 0 : directionWeight);

            if (cost < dis[i][dx][dy]) {
                dis[i][dx][dy] = cost;
                Cell next(dx, dy, i);
                pre[next] = cur;
                if (vis[next] == 0) {
                    vis[next] = 1;
                    que.push(next);
                }
            }
        }
    }
    int res = INT_MAX;
    Cell now;
    for (int i = 0; i < 4; i++) {
        if (res > dis[i][dest.x][dest.y]) {
            res = dis[i][dest.x][dest.y];
            now = Cell(dest.x, dest.y, i);
        }
    }
    std::vector<Cell> path;
    int cnt = 0;
    if (res == INT_MAX) {
        std::cout << "can not find the path!" << std::endl;
    } else {
        std::cout << "find a path, cost is " << res << std::endl;
        do {
          path.push_back(now);
          now = pre[now];

        } while (now.x != start.x || now.y != start.y);
        reverse(path.begin(), path.end());
    }
    return path;
  }

}