#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
using std::cout, std::vector, std::string, std::ifstream, std::unordered_map;

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
    int getX() {return x;}
};

struct Path {
    int id1;
    int id2;
    int64_t distance;
    Path(int _id1, int _id2, int64_t dist) {
        id1 = _id1;
        id2 = _id2;
        distance = dist;
    }
};
bool compPath(Path* a, Path* b) {
    return a->distance < b->distance;
}
bool compMax(int x, int y) {
    return x > y;
}
class Circuits{
    vector<int> groupings;
    int id;

    /* Iterates through groupings, replacing any values equal to targetG with newG */
    void linkGroups(int targetG, int newG) {
        for (uint i = 0; i < groupings.size(); i++) {
            if (groupings[i] == targetG) { groupings[i] = newG; }
        }
    }

    public:
    Circuits(uint points) {
        id = 0;
        groupings = vector<int>(points, -1);
    }
    void checkGrouping() {
        for (uint i = 0; i < groupings.size(); i++) {
            printf("%i %d\n", i, groupings[i]);
        }
    }

    /* Given two ids, places both ids in the same group, using the smallest id of the two. */
    void combinePts(int id1, int id2) {
        int g1 = groupings[id1];
        int g2 = groupings[id2];
        if ((g1 == -1) && (g2 == -1)) { 
            // Neither point is in a group; assign a new group_id
            groupings[id1] = id;
            groupings[id2] = id;
            id++;
            return;
        } 
        if (g1 == -1) {
            groupings[id1] = g2;
            return;
        }
        if (g2 == -1) {
            groupings[id2] = g1;
            return;
        }
        else {
            // Both points are in a group, need to connect two groups
            int smallest = std::min(g1, g2);
            int largest = std::max(g1, g2);
            linkGroups(smallest, largest);
        }
    }

    /* Returns a vector containing the three largest integers */
    vector<int> largestCircuits() {
        unordered_map<int, int> map;
        for (uint i = 0; i < groupings.size(); i++) {
            if (groupings[i] != -1) {
                if (map.find(groupings[i]) == map.end()) {
                    map[groupings[i]] = 1;
                }
                else {
                    map[groupings[i]]++;
                }
            }
        }
        vector<int> buffer;
        for (auto iter = map.begin(); iter != map.end(); iter++) {
            buffer.push_back(iter->second);
        }
        std::sort(buffer.begin(), buffer.end(), &compMax);
        vector<int> largest;
        for (int i = 0; i < 3; i++) {
            largest.push_back(buffer[i]);
        }
        return largest;
    }
    /* Returns a vector containing the three largest integers */
    int largestCircuit() {
        unordered_map<int, int> map;
        for (uint i = 0; i < groupings.size(); i++) {
            if (groupings[i] != -1) {
                if (map.find(groupings[i]) == map.end()) {
                    map[groupings[i]] = 1;
                }
                else {
                    map[groupings[i]]++;
                }
            }
        }
        vector<int> buffer;
        for (auto iter = map.begin(); iter != map.end(); iter++) {
            buffer.push_back(iter->second);
        }
        std::sort(buffer.begin(), buffer.end(), &compMax);
        return buffer[0];
    }
};

void Part1(string filename, uint links) {
    ifstream file;
    file.open(filename);
    vector<Point*> points;
    int x, y, z;
    while (file >> x >> y >> z) {
        // printf("%i %i %i\n", x, y, z);
        Point* point = new Point(x,y,z);
        points.push_back(point);
    }
    file.close();

    // printf("Points Size: %li\n", points.size());
    vector<Path*> paths;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Path* path = new Path(i, j, points[i]->distanceTo(points[j]));
            paths.push_back(path);
        }
    }
    // printf("Paths Size: %li\n", paths.size());

    std::sort(paths.begin(),paths.end(), &compPath);
    Circuits circuits(points.size());
    
    for (uint i = 0; i < links; i++) {
        int id1, id2;
        id1 = paths[i]->id1;
        id2 = paths[i]->id2;
        circuits.combinePts(id1, id2);
    }
    
    vector<int> largest = circuits.largestCircuits();
    int prod = 1;
    for(uint i = 0; i < largest.size(); i++) {
        // printf("%i\n", largest[i]);
        prod *= largest[i];
    }
    printf("PART 1: %i\n", prod);
}
void Part2(string filename) {
    ifstream file;
    file.open(filename);
    vector<Point*> points;
    int x, y, z;
    while (file >> x >> y >> z) {
        // printf("%i %i %i\n", x, y, z);
        Point* point = new Point(x,y,z);
        points.push_back(point);
    }
    file.close();

    // printf("Points Size: %li\n", points.size());
    vector<Path*> paths;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Path* path = new Path(i, j, points[i]->distanceTo(points[j]));
            paths.push_back(path);
        }
    }
    // printf("Paths Size: %li\n", paths.size());

    std::sort(paths.begin(),paths.end(), &compPath);
    Circuits circuits(points.size());
    int count = 0;
    for (auto iter = paths.begin(); iter != paths.end(); iter++) {
        int id1, id2;
        id1 = (*iter)->id1;
        id2 = (*iter)->id2;
        circuits.combinePts(id1, id2);
        count++;
        if (circuits.largestCircuit() == (int)points.size()) {
            // cout << circuits.largestCircuit() << '\n';
            int64_t x1 = points[id1]->getX();
            int64_t x2 = points[id2]->getX();
            uint64_t prod = x1 * x2;
            // cout << INT64_MAX << '\n';
            // cout << prod << '\n';
            // printf("%ld * %ld = %ld\n", x1, x2, prod);
            printf("PART 2: %ld\n", prod);
            return;
        }
    }
}
int main() {
    Part1("inputs/input.txt", 1000);    // Part 1: 153328
    Part2("inputs/input.txt");          // Part 2: 6095621910
    /* PART 2:
    5244 - too low; this is the 5244th link, need to return the product of the two id's
    1800654614 - too low, check int overflow 
    6095621910 - Correct! Since Points stored each coordinate as an int, the product of calling x1*x2 was int. 
    Need to either cast the int to int64_t before calling mul or store the coordinates as int64_t*/
    
}