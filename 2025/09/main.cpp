#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
using std::cout, std::ifstream, std::vector, std::abs, std::unordered_map, std::string, std::queue;

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

int64_t calcArea(Point p1, Point p2) {
    return (abs(p1.x - p2.x)+1) * (abs(p1.y - p2.y)+1);
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
    vector<Point> corners{a};
    corners.push_back(Point{a.x, b.y});
    corners.push_back(b);
    corners.push_back(Point{b.x, a.y});
    return corners;
}

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
    int originalRow(int compRow) { return OriginalRows[compRow]; }
    int originalCol(int compCol) { return OriginalCols[compCol]; }
    Point compressedPoint(Point p) {
        return Point{compressedCol(p.x), compressedRow(p.y)};
    }
    Point originalPoint(Point p) {
        return Point{originalCol(p.x), originalRow(p.y)};
    }
    int getM() { return m; }
};

class BoolMap {
    vector<vector<bool>> map;
    public:
    BoolMap(int m) {
        for (int i = 0; i < m; i++) {
            map.push_back(vector<bool>(m));
        }
    }
    bool get(int r, int c) { return map[r][c]; }
    void set(int r, int c, bool val) { map[r][c] = val; }
};

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
        printf("ERROR ");
        return false;
    }
    return true;
}

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

void part2() {
    string input = "inputs/input.txt";

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
    BoolMap periMap(M);
    // Initialize perimeter map; Row Major (x,y) = [y][x]
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            periMap.set(r, c, 0);
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
            for (int ROW = MIN; ROW <= MAX; ROW++) {
                periMap.set(ROW, prev.x, 1);
            }
        }
        else if (prev.y == curr.y) {
            // Traverse by cols
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
    compressedPoints.pop_back();

    //PRINT Perimeter map
    // for (int r = 0; r < M; r++) {
    //     for (int c = 0; c < M; c++) {
    //         if (periMap.get(r, c)) {
    //             cout << '#';
    //         }
    //         else {
    //             cout << '.';
    //         }
    //     }
    //     cout << '\n';
    // }

    // BFS
    BoolMap visited(M);
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            visited.set(r,c,false);
        }
    }
    BoolMap invalidTiles(M);
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < M; c++) {
            invalidTiles.set(r, c, false);
        }
    }

    queue<Point> BFSqueue;
    BFSqueue.push(Point{0,0});
    int r, c;
    while (!BFSqueue.empty()) {
        Point p = BFSqueue.front();
        c = p.x;
        r = p.y;
        BFSqueue.pop();
        if ((r >= M) || (r < 0) || (c >= M) || (c < 0)) { continue; }
        if ((!visited.get(r,c)) && (!periMap.get(r,c))) {
            visited.set(r,c,true);
            invalidTiles.set(r,c,true);
            vector<Point> adj = adjacentPoints(p);
            for (auto iter = adj.begin(); iter != adj.end(); iter++) {
                BFSqueue.push(*iter);
            }
        }
    }

    // PRINT invalid tiles
    // cout << '\n';
    // for (int r = 0; r < M; r++) {
    //     for (int c = 0; c < M; c++) {
    //         if (invalidTiles.get(r,c)) {
    //             cout <<'X';
    //         }
    //         else {
    //             cout << '.';
    //         }
    //     }
    //     cout << '\n';
    // }

    vector<int64_t> areas;
    int64_t area;
    // for (auto iter = compressedPoints.begin(); iter != compressedPoints.end(); iter++) {
    //     printf("(%ld, %ld)\n", iter->x, iter->y);
    // }
    // ITERATE THROUGH COMPRESSED POINTS (red tiles) and check all areas between (CompP x ComP)
    for (auto iter1 = compressedPoints.begin(); iter1 != compressedPoints.end(); iter1++) {
        for (auto iter2 = iter1+1; iter2 != compressedPoints.end(); iter2++) {
            Point p1, p2;
            p1 = *iter1;
            p2 = *iter2;
            if ((p1.x == p2.x) && (p1.y == p2.y)) { continue; }
            if (validArea(p1, p2, &invalidTiles)) {
                area = calcArea(compMap.originalPoint(p1), compMap.originalPoint(p2));
                // printf("VALID: (%ld, %ld) and (%ld, %ld) %ld\n", p1.x,p1.y,p2.x,p2.y,area);
                areas.push_back(area);
            }
        }
    }
    std::sort(areas.begin(), areas.end(), &intMax);
    printf("PART 2: %ld\n", areas[0]);
}
int main() {
    part1(); // 4715966250 
    part2(); // 1530527040
    /* PART 2:
    4678171871 TOO HIGH
    AOC HINTS:
    1. Line Intersections
    2. Coordinate Compression (*) <- makes the most sense!
    1530527040 after refactor!
    */
}