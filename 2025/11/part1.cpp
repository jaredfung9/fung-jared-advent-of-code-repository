#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
using std::cout, std::vector, std::string, std::unordered_map, std::ifstream, std::stringstream, std::stack;

typedef unordered_map<string, vector<string>> childrenMap; 
typedef unordered_map<string, int> pathMap;

childrenMap buildChildrenMap(string filename) {
    unordered_map<string, vector<string>> map;
    ifstream file;
    file.open(filename);
    string buffer;
    while(getline(file, buffer)) {
        stringstream strm(buffer);
        string key, val;
        strm >> key;
        key = key.substr(0,key.size()-1);
        vector<string> vals;
        while (strm >> val) {
            vals.push_back(val);
        }
        map[key] = vals;
    }
    file.close();
    return map;
}

int pathsToOut(childrenMap* map) {
    int count = 0;
    stack<vector<string>> paths;
    vector<string> path;
    path.push_back("you");
    paths.push(path);
    vector<string> children;
    while (!paths.empty()) {
        path = paths.top();
        paths.pop();
        if (path.back() == "out") {
            count++;
            continue;
        }
        children = (*map)[path.back()];
        for (int i = 0; i < (int) children.size(); i++) {
            bool visited = false;
            for (int j = 0; j < (int) path.size(); j++) {
                if (path[j] == children[i]) {
                    visited = true;
                }
            }
            if (!visited) {
                vector<string> next_path(path);
                next_path.push_back(children[i]);
                paths.push(next_path);
            }
        }
    }
    cout << count << '\n';
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please include a filename:\n");
        return -1;
    }
    childrenMap childMap = buildChildrenMap(argv[1]);
    pathsToOut(&childMap); // Part 1: 674
}