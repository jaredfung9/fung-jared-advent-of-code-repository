#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using std::cout, std::vector, std::string, std::ifstream;

class Point {
    int x, y, z;
    public:
    Point(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    int64_t distanceTo(Point* b) {
        return pow(x - b->x, 2) + pow(y - b->y, 2) + pow(z - b->z, 2);
    }
};

struct Path {
    int id1;
    int id2;
    int64_t distance;
};

void Part1() {
    string filename = "inputs/demo.txt";
    ifstream file;
    file.open(filename);
    vector<Point*> points;
    int x, y, z;
    while (file >> x >> y >> z) {
        printf("%i %i %i\n", x, y, z);
        Point* point = new Point(x,y,z);
        points.push_back(point);
    }
    printf("Points Size: %li\n", points.size());
    file.close();
}
int main() {
    Part1();
}