#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using std::cout, std::ifstream, std::vector, std::abs;

struct Point {
    int64_t x, y;
};
bool intMax(int64_t a, int64_t b) {
    return a > b;
}
int main() {
    // Part 1:
    ifstream file;
    file.open("inputs/demo.txt");
    vector<Point> points;
    int64_t _x, _y;
    while (file >> _x >> _y) {
        points.push_back(Point{_x, _y});
    }
    file.close();

    // for (auto iter = points.begin(); iter != points.end(); iter++) {
    //     printf("%ld %ld\n", iter->x, iter->y);
    // }

    vector<int64_t> areas;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Point p1 = points[i];
            
            Point p2 = points[j];
            // printf("Point 1: %ld %ld\n", p1.x, p1.y);
            // printf("Point 2: %ld %ld\n", p2.x, p2.y);
            int64_t area = (abs(p1.x - p2.x)+1) * (abs(p1.y - p2.y)+1);
            // printf("%ld\n", area);
            areas.push_back(area);
        }
    }
    std::sort(areas.begin(), areas.end(), &intMax);
    printf("PART 1: %ld\n", areas[0]);
}