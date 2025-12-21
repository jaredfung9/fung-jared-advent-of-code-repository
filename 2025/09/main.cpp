#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using std::cout, std::ifstream, std::vector, std::abs, std::unordered_map;

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
It seems like each row and column has a pair of points.
consider the following case study:

        ...#X#
        ...X.X
        #XX#.X
        X....X
 (0,0)->#XXXX#

Points:
(0,0)
(5,0)
(5,4)
(3,4)
(3,2)
(0,2)

Ranges  
Col         Row
0 : 0,2     0 : 0,5
5 : 0,4     4 : 3,5
3 : 2,4     2 : 0,3

Invalid Area:
(0,2) (3,4)
Valid Area:
(0,2) (5,0)

Corners
(x1,y1) (x2, y2) -> (x1,y2) (x2,y1)
[(0,2) (3,4)] (0,4) (3,2) <- calculate other corners
[(0,2) (5,0)] (0,0) (5,2)
check if each corner is in range

Is it okay to return validCols | validRows or do we need both Cols and Rows to be valid?
A valid area will pass at least one range check.
An invalid area is unable to pass any test because it neither has a valid row or col.
*/

/* Contains a set of valid row and col ranges.
Can be used to check if a corner is in range. */
// class Ranges {
// };
vector<Point> genCorners(Point a, Point b) {
    vector<Point> corners{a, b};
    corners.push_back(Point{a.x, b.y});
    corners.push_back(Point{b.x, a.y});
    return corners;
}

void part2() {
    Point a{0,2};
    Point b{5,0};
    vector<Point> corners = genCorners(a, b);
    for (auto iter = corners.begin(); iter != corners.end(); iter++) {
        printf("%ld %ld\n", iter->x, iter->y);
    }
}
int main() {
    part1(); // 4715966250 
    part2();
}