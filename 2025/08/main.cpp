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
    Path(int _id1, int _id2, int64_t dist) {
        id1 = _id1;
        id2 = _id2;
        distance = dist;
    }
};
bool compPath(Path* a, Path* b) {
    return a->distance < b->distance;
}
class Circuits{
    vector<int> groupings;
    int id;
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

    vector<Path*> paths;
    for (uint i = 0; i < points.size(); i++) {
        for (uint j = i+1; j < points.size(); j++) {
            Path* path = new Path(i, j, points[i]->distanceTo(points[j]));
            paths.push_back(path);
        }
    }
    
    printf("Paths Size: %li\n", paths.size());
    for (uint i = 0; i < paths.size(); i++) {
        cout << paths[i]->distance <<'\n';
    }
    printf("\nSORTED\n\n");
    std::sort(paths.begin(),paths.end(), &compPath);
    for (uint i = 0; i < paths.size(); i++) {
        printf("%d, %d ", paths[i]->id1, paths[i]->id2);
        cout << paths[i]->distance<<'\n';
    }
    file.close();
}
int main() {
    Part1();
}