#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

using std::shared_ptr, std::vector, std::string, std::ifstream, std::cout;
typedef struct {
    int64_t first;
    int64_t second;
}Range;

typedef shared_ptr<Range> RangePtr;

shared_ptr<vector<RangePtr>> loadRange(string* filename) {
    ifstream file;
    file.open(*filename);
    auto ranges = std::make_shared<vector<RangePtr>>();
    int64_t a, b;
    while (!file.eof()) {
        file >> a >> b;
        auto block = std::make_shared<Range>();
        block->first = a;
        block->second = b;
        ranges->push_back(block);
    }
    file.close();
    return ranges;
}

void printRange(shared_ptr<vector<RangePtr>> ranges) {
    for (auto it = ranges->begin(); it != ranges->end(); ++it) {
        cout << it[0]->first << ' '  << it[0]->second << '\n';
    }
}
int main() {
    string input = "inputs/test-ranges.txt";
    shared_ptr<vector<RangePtr>> ranges = loadRange(&input);
    printRange(ranges);
}