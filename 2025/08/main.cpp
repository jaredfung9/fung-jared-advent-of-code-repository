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

        // for (auto iter = buffer.begin(); iter != buffer.end(); iter++) {
        //     printf("%i\n", (*iter));
        // }
        vector<int> largest;
        for (int i = 0; i < 3; i++) {
            largest.push_back(buffer[i]);
        }
        return largest;
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

    printf("Points Size: %li\n", points.size());
    vector<Path*> paths;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Path* path = new Path(i, j, points[i]->distanceTo(points[j]));
            paths.push_back(path);
        }
    }
    printf("Paths Size: %li\n", paths.size());

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
int main() {
    Part1("inputs/input.txt", 1000);    // Part 1: 153328
    
}