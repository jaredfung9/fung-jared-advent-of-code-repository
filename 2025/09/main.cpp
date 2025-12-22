/* Advent of Code 2025 - Day 09 - JARED FUNG */
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
using std::cout, std::ifstream, std::vector, std::abs, std::unordered_map, std::string, std::queue;

/* PART 1 */
struct Point {
    int64_t x, y;
};
bool compPoint(Point a, Point b) {
    return a.x < b.x;
}

bool intMax(int64_t a, int64_t b) {
    return a > b;
}

int64_t calcArea(Point p1, Point p2) {
    return (abs(p1.x - p2.x)+1) * (abs(p1.y - p2.y)+1);
}

void part1(string input) {
    ifstream file;
    file.open(input);
    vector<Point> points;
    int64_t _x, _y;
    while (file >> _x >> _y) {
        points.push_back(Point{_x, _y});
    }
    file.close();

    vector<int64_t> areas;
    int64_t area;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Point p1 = points[i];
            Point p2 = points[j];
            area = calcArea(p1, p2);
            areas.push_back(area);
        }
    }
    std::sort(areas.begin(), areas.end(), &intMax);
    printf("PART 1: %ld\n", areas[0]);
}

/* PART 2 */
/* Helpers for sorting vector<Point> objects. */
bool sortByRow(Point a, Point b) { return a.y < b.y; } 
bool sortByCol(Point a, Point b) { return a.x < b.x; } 

/* Given the points of two opposite corners A and B, returns a vector of points representing the corners of the rectangle formed by A and B. */
vector<Point> genCorners(Point a, Point b) {
    vector<Point> corners{a};
    corners.push_back(Point{a.x, b.y});
    corners.push_back(b);
    corners.push_back(Point{b.x, a.y});
    return corners;
}

/* Given a point P, returns potential adjacent points. DOES NOT PERFORM RANGE VALIDATION. */
vector<Point> adjacentPoints(Point p) {
    vector<Point> adj;
    adj.push_back(Point{p.x+1, p.y});
    adj.push_back(Point{p.x-1, p.y});
    adj.push_back(Point{p.x, p.y+1});
    adj.push_back(Point{p.x, p.y-1});
    return adj;
}

class CompressedMapping {
    unordered_map<int, int> CompressedRows; // ORIGINAL -> COMPRESSED
    unordered_map<int, int> CompressedCols;
    unordered_map<int, int> OriginalRows; // COMPRESSED -> ORIGINAL
    unordered_map<int, int> OriginalCols; 
    int m; // indicates the compressed range [0,m]
    public:
    CompressedMapping(string filename) {
        ifstream file;
        file.open(filename);
        vector<Point> points;
        int x,y;
        while (file >> x >> y) { points.push_back(Point{x,y}); }
        file.close();

        // Build Compressed Rows
        std::sort(points.begin(), points.end(), sortByRow);
        int i = 1;
        for (auto iter = points.begin(); iter != points.end(); iter++) {
            int row = iter->y;
            if (CompressedRows[row] == 0) { // Ignore duplicates by only inserting if lookup is empty
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
        m = i+1; // Insert Buffer Space
    }
    int compressedRow(int originalRow) { return CompressedRows[originalRow]; }
    int compressedCol(int originalCol) { return CompressedCols[originalCol]; }
    int originalRow(int compRow) { return OriginalRows[compRow]; }
    int originalCol(int compCol) { return OriginalCols[compCol]; }
    Point compressedPoint(Point p) { return Point{compressedCol(p.x), compressedRow(p.y)}; }
    Point originalPoint(Point p) { return Point{originalCol(p.x), originalRow(p.y)}; }
    int getM() { return m; }
};

/* 2D Bool Map - Row Major */
class BoolMap {
    vector<vector<bool>> map;
    int N;
    public:
    BoolMap(int n) { 
        for (int i = 0; i < n; i++) { map.push_back(vector<bool>(n, 0)); } 
        N = n;
    }
    bool get(int r, int c) { return map[r][c]; }
    void set(int r, int c, bool val) { map[r][c] = val; }
    int getN() { return N; }
};

/* Used to print BoolMap for analysis */
void printMap(char valid, char invalid, BoolMap* map) {
    for (int r = 0; r < map->getN(); r++) {
        for (int c = 0; c < map->getN(); c++) {
            if (map->get(r,c)) {
                cout << valid;
            }
            else {
                cout << invalid;
            }
        }
        cout << '\n';
    }
}
/* Given two points A and B and a BoolMap representing INVALID tiles,
walks between A and B in a straight line, checking if each tile is valid.
Returns False if any tile along the path is invalid. Otherwise, returns True. */
bool validStraight(Point a, Point b, BoolMap* invalid) {
    int MIN,MAX;
    if (a.x == b.x) {
        MIN = std::min(a.y, b.y);
        MAX = std::max(a.y, b.y);
        for (int r = MIN; r <= MAX; r++) {
            if (invalid->get(r,a.x)) { return false; }    
        }
    }
    else if (a.y == b.y) {
        MIN = std::min(a.x, b.x);
        MAX = std::max(a.x, b.x);
        for (int c = MIN; c <= MAX; c++) {
            if (invalid->get(a.y, c)) { return false; }
        }
    }
    else {
        printf("ERROR: Invalid Move Given (%ld, %ld) -> (%ld, %ld)\n", a.x, a.y, b.x, b.y);
        return false;
    }
    return true;
}

/* Given two points A and B and BoolMap of INVALID tiles, checks whether the area formed by using A and B as opposite corners of a rectangle
is valid. */
bool validArea(Point a, Point b, BoolMap* invalid) {
    vector<Point> corners = genCorners(a,b);
    Point curr, next;

    for (int i = 0; i < (int) corners.size()-1; i++) {
        curr = corners[i];
        next = corners[i+1];
        if (!validStraight(curr, next, invalid)) { return false; }    
    }
    // check final straight
    if (!validStraight(corners.back(), corners.front(), invalid)) { return false; }
    return true;
}

void part2(string input) {
    ifstream file;
    file.open(input);
    vector<Point> points;
    int64_t _x, _y;
    while (file >> _x >> _y) {
        points.push_back(Point{_x, _y});
    }
    file.close();
    
    CompressedMapping compMap = CompressedMapping(input);  
    vector<Point> compressedPoints;                                     // Convert input into compressed points
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        compressedPoints.push_back(compMap.compressedPoint(*iter));
    }

    int M = compMap.getM();
    BoolMap periMap(M);                                                 // Build Perimeter
    compressedPoints.push_back(compressedPoints[0]);                    // Push the starting point to the end of our list so that we close the loop.
    Point prev = compressedPoints[0];
    Point curr;
    int MIN, MAX;
    for (int i = 1; i < (int) compressedPoints.size(); i++) {
        curr = compressedPoints[i];
        if (prev.x == curr.x) {
            // Traverse vertically (by rows()
            MIN = std::min(prev.y, curr.y);
            MAX = std::max(prev.y, curr.y);
            for (int ROW = MIN; ROW <= MAX; ROW++) {
                periMap.set(ROW, prev.x, 1);
            }
        }
        else if (prev.y == curr.y) {
            // Traverse horizontally (by cols)
            MIN = std::min(prev.x, curr.x);
            MAX = std::max(prev.x, curr.x);
            for (int COL = MIN; COL <= MAX; COL++) {
                periMap.set(prev.y, COL, 1);
            }
        }
        else {
            printf("FATAL ERROR: ILLEGAL MOVE %ld %ld -> %ld %ld\n", prev.x, prev.y, curr.x, curr.y);
            return;
        }
        prev = curr;
    }
    compressedPoints.pop_back();                                        // Remove the starting point that we used to close the loop.

    BoolMap visited(M);                                                 // BFS to flag invalid tiles
    BoolMap invalidTiles(M);

    queue<Point> BFSqueue;
    BFSqueue.push(Point{0,0});                                          // The point (0,0) in our compressed coordinates will always be invalid by construction.
    int r, c;
    while (!BFSqueue.empty()) {
        Point p = BFSqueue.front();
        BFSqueue.pop();
        c = p.x;
        r = p.y;

        if ((r >= M) || (r < 0) || (c >= M) || (c < 0)) { continue; }   // adjacentPoints() does not perform range validation.
        if ((!visited.get(r,c)) && (!periMap.get(r,c))) {
            visited.set(r,c,true);
            invalidTiles.set(r,c,true);
            vector<Point> adj = adjacentPoints(p);
            for (auto iter = adj.begin(); iter != adj.end(); iter++) {
                BFSqueue.push(*iter);
            }
        }
    }

    // printMap('#','.',&periMap);                                      // DEBUG: Print perimeter map

    // printMap('o','.',&invalidTiles);                                 // DEBUG : Print invalid range


    // Iterate through our list of compressed points, picking two opposite corners and performing a validation check.
    // 
    vector<int64_t> areas;
    int64_t area;
    for (auto iter1 = compressedPoints.begin(); iter1 != compressedPoints.end(); iter1++) {
        for (auto iter2 = iter1+1; iter2 != compressedPoints.end(); iter2++) {
            Point p1, p2;
            p1 = *iter1;
            p2 = *iter2;
            if (validArea(p1, p2, &invalidTiles)) {
                area = calcArea(compMap.originalPoint(p1), compMap.originalPoint(p2)); // Calculate the area after converting back into original domain.
                areas.push_back(area);
            }
        }
    }
    std::sort(areas.begin(), areas.end(), &intMax);
    printf("PART 2: %ld\n", areas[0]);
}
int main() {
    string input = "inputs/input.txt";
    part1(input); // 4715966250 
    part2(input); // 1530527040

    /* PART 2:
    4678171871 TOO HIGH
    AOC HINTS:
    1. Line Intersections
    2. Coordinate Compression (*) <- makes the most sense!
    1530527040 after refactor!
    */
}