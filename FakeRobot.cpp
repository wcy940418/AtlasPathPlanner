#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class RobotPosition {
    public:
        vector<int> position;
        double orientation;
};

class FakeRobot {
    public:
        FakeRobot(int rad, int len, int br, RobotPosition p) {
            radius = rad;
            length = len;
            breadth = br;
            pos = p;
        }

        void run() {
            vector<double> linearSpeed;
            vector<int> x_speed;
            vector<int> y_speed;
            int isTurning = 0;
            for (auto i = robotSpeed.begin(); i != robotSpeed.end(); i++) {
                if(*i < 0) {
                    isTurning++;
                }
                double speed = *i * radius * 2 * 3.14 / 60;
                linearSpeed.push_back(speed);
                x_speed.push_back(speed * cos(pos.orientation * 3.14/180));
                y_speed.push_back(speed * sin(pos.orientation * 3.14/180));
            }
            if(isTurning == 0) {
                pos.position[0] = pos.position[0] + x_speed[0] * update_rate;
                pos.position[1] = pos.position[1] + y_speed[0] * update_rate;
                pos.orientation = pos.orientation;
            } else if (isTurning == 4) {
                pos.position[0] = pos.position[0] + x_speed[0] * update_rate;
                pos.position[1] = pos.position[1] + y_speed[0] * update_rate;
                pos.orientation = pos.orientation + 180;
            } else if (isTurning == 2) {
                pos.position[0] = pos.position[0];
                pos.position[1] = pos.position[1];
                pos.orientation = pos.orientation + (linearSpeed[0] * update_rate * 360 / (3.14 * length));
            }
        }

        void setSpeeds(vector<int> speeds) {
            robotSpeed[0] = speeds[0];
            robotSpeed[1] = speeds[1];
            robotSpeed[2] = speeds[2];
            robotSpeed[3] = speeds[3];
        }

        RobotPosition getPosition() {
            return pos;
        }

    private:
        int update_rate;
        int radius;
        int length;
        int breadth;
        vector<int> robotSpeed;
        RobotPosition pos;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}