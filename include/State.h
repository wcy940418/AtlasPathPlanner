#ifndef _LIBCPP_ROBOT_STATE
#define _LIBCPP_ROBOT_STATE

class State {
public:
  int x, y;
  int dir;
  State();
  State(int x, int y, int dir);
  bool operator < (const State& state) const;
};

#endif

