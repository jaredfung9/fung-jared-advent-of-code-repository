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
void part1() {
    // Part 1:
    ifstream file;
    file.open("inputs/input.txt");
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
    // printf("AREAS: %ld\n", areas.size());
    printf("PART 1: %ld\n", areas[0]); // 4715966250
}
/* Brainstorm: It is possible to initialize a 100000x100000 bool map to indicate if a tile is valid. 
Input list walks us around the perimeter. Maybe we can identify valid ranges for each row and column. 
Leverage the fact that each line indicates a move (we only move by a column or row) to identify the min and max of each row and column.
It seems like each row and column has a pair of points.*/
// void big() {
//     const int n = 100000;
//     vector<vector<bool>>rows;
//     for (int i = 0; i < n; i++) {
//         vector<bool> row(n, true);
//         rows.push_back(row);
//     }
//     if (rows[96759][38236]) {
//         printf("finished");
//     }
// }

bool compPoint(Point a, Point b) {
    return a.x < b.x;
}
void checkPoints() {
    ifstream file;
    file.open("inputs/input.txt");
    vector<Point> points;
    int64_t _x, _y;
    while (file >> _x >> _y) {
        points.push_back(Point{_x, _y});
    }
    file.close();
    std::sort(points.begin(), points.end(), &compPoint);
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        printf("%ld\n", iter->x);
    }
}
int main() {
    part1(); // 4715966250
    // checkPoints();
    // big();
    
}