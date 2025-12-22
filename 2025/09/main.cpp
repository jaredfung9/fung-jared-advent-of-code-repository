#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <set>
using std::cout, std::ifstream, std::vector, std::abs, std::unordered_map, std::string;

struct Point {
    int64_t x, y;
};
bool sortByRow(Point a, Point b) { return a.y < b.y; }

bool sortByCol(Point a, Point b) { return a.x < b.x; }

bool compPoint(Point a, Point b) {
    return a.x < b.x;
}
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

    vector<int64_t> areas;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Point p1 = points[i];
            Point p2 = points[j];
            int64_t area = (abs(p1.x - p2.x)+1) * (abs(p1.y - p2.y)+1);
            areas.push_back(area);
        }
    }
    std::sort(areas.begin(), areas.end(), &intMax);
    printf("PART 1: %ld\n", areas[0]); // 4715966250
}

/* PART 2 */
vector<Point> genCorners(Point a, Point b) {
    vector<Point> corners{a, b};
    corners.push_back(Point{a.x, b.y});
    corners.push_back(Point{b.x, a.y});
    return corners;
}

class CompressedMapping {
    unordered_map<int, int> CompressedRows; // ORIGINAL -> COMPRESSED
    unordered_map<int, int> CompressedCols;
    unordered_map<int, int> OriginalRows;
    unordered_map<int, int> OriginalCols; // COMPRESSED -> ORIGINAL
    int m;
    public:
    CompressedMapping(string filename) {
        ifstream file;
        file.open(filename);
        vector<Point> points;
        int x,y;
        while (file >> x >> y) {
            points.push_back(Point{x,y});
        }
        file.close();
        // Build Compressed Rows
        std::sort(points.begin(), points.end(), sortByRow);
        int i = 1;
        for (auto iter = points.begin(); iter != points.end(); iter++) {
            int row = iter->y;
            if (CompressedRows[row] == 0) { // Ignore duplicates
                CompressedRows[row] = i;
                OriginalRows[i] = row;
                i += 2;
            }
        }
        // Build Compressed Cols
        std::sort(points.begin(), points.end(), sortByCol);
        i = 1;
        for (auto iter = points.begin(); iter != points.end(); iter++) {
            int col = iter->x;
            if (CompressedCols[col] == 0) {
                CompressedCols[col] = i;
                OriginalCols[i] = col;
                i += 2;
            }
        }
        m = i + 1; // Insert Buffer Space
    }
    int compressedRow(int originalRow) { return CompressedRows[originalRow]; }
    int compressedCol(int originalCol) { return CompressedCols[originalCol]; }
    Point compressedPoint(Point p) {
        return Point{compressedCol(p.x), compressedRow(p.y)};
    }
    int getM() { return m; }
};
void part2() {
    string input = "inputs/demo.txt";
    printf("PART 2:\n");
    ifstream file;
    file.open(input);
    vector<Point> points;
    int64_t _x, _y;
    while (file >> _x >> _y) {
        points.push_back(Point{_x, _y});
    }
    file.close();
    
    CompressedMapping compMap = CompressedMapping(input);  
    vector<Point> compressedPoints;
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        compressedPoints.push_back(compMap.compressedPoint(*iter));
    }
    int M = compMap.getM();
    bool periMap[M][M]; // Initialize perimeter map; Row Major (x,y) = [y][x]
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            periMap[r][c] = 0;
        }
    }
    compressedPoints.push_back(compressedPoints[0]);
    Point prev = compressedPoints[0];
    Point curr;
    int MIN, MAX;
    for (int i = 1; i < (int) compressedPoints.size(); i++) {
        curr = compressedPoints[i];
        if (prev.x == curr.x) {
            // Traverse by rows
            MIN = std::min(prev.y, curr.y);
            MAX = std::max(prev.y, curr.y);
            // printf("MOVING VERTICALLY %ld %ld -> %ld %ld FROM %d -> %d\n", prev.x, prev.y, curr.x, curr.y, MIN, MAX);
            for (int ROW = MIN; ROW <= MAX; ROW++) {
                periMap[ROW][prev.x] = 1;
            }
        }
        else if (prev.y == curr.y) {
            // Traverse by cols
            MIN = std::min(prev.x, curr.x);
            MAX = std::max(prev.x, curr.x);
            // printf("MOVING HORIZONTALLY %ld %ld -> %ld %ld FROM %d -> %d\n", prev.x, prev.y, curr.x, curr.y, MIN, MAX);
            for (int COL = MIN; COL <= MAX; COL++) {
                periMap[prev.y][COL] = 1;
            }
        }
        else {
            printf("FATAL ERROR: ILLEGAL MOVE %ld %ld -> %ld %ld\n", prev.x, prev.y, curr.x, curr.y);
        }
        prev = curr;
    }

    // PRINT PERIMETER MAP TIME
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            if (periMap[r][c]) {
                cout << '#';
            }
            else {
                cout << '.';
            }
        }
        cout << '\n';
    }

    // BFS
}
int main() {
    part1(); // 4715966250 
    part2();
    /* PART 2:
    4678171871 TOO HIGH
    AOC HINTS:
    1. Line Intersections
    2. Coordinate Compression
    */
}