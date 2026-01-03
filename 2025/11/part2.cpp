#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
using std::cout, std::vector, std::string, std::unordered_map, std::ifstream, std::stringstream, std::stack;

typedef unordered_map<string, vector<string>> childrenMap; 
class pathCache {
    unordered_map<string, unordered_map<string, int64_t>> _cache;
    public:
    pathCache() {}
    int lookup(string a, string b) {
        auto cacheResult = _cache.find(a);
        if (cacheResult != _cache.end()) {
            auto mapResult = cacheResult->second.find(b);
            if (mapResult != cacheResult->second.end()) {
                return mapResult->second;
            }
        }
        return -1;
    }
    void set(string a, string b, int64_t count) {
        _cache[a][b] = count;
    }
};

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

pathCache _cache;   /* Memoization */
int64_t countPaths(string start, string end, childrenMap* map) {
    int64_t cacheResult = _cache.lookup(start,end);
    if (cacheResult != -1) {
        return cacheResult;
    }
    int64_t count = 0;
    vector<string> children = (*map)[start];
    if (start == end) { return 1; }
    if (children.size() <= 0) { return 0; }
    for (int i = 0; i < (int) children.size(); i++) {
        count += countPaths(children[i], end, map);
    }
    _cache.set(start, end, count);
    return count;
}

/* Calculates all possible paths from svr to out that include fft and dac somewhere in the path. */
int64_t calculateSvrToOut(childrenMap* map) {
    int64_t sTof = countPaths("svr", "fft", map);
    int64_t fTod = countPaths("fft", "dac", map);
    int64_t dToo = countPaths("dac", "out", map);

    int64_t sTod = countPaths("svr", "dac", map);
    int64_t dTof = countPaths("dac", "fft", map);
    int64_t fToo = countPaths("fft", "out", map);
    return sTof*fTod*dToo + sTod*dTof*fToo;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please include a filename:\n");
        return -1;
    }

    childrenMap map = buildChildrenMap(argv[1]);
    cout << calculateSvrToOut(&map) << '\n';    // PART 2: 438314708837664
    /* PART 2: NOTES
    To calculate the paths from svr -> out that visit both fft and dac:
    (svr->fft)*(fft->dac)*(fft->out)
    (svr->dac)*(dac->fft)*(fft->out)
    
    To speed up calculations, implement memoization.

    Our input appears to be a DAG, therefore we can skip checking for cycles.
    */
}