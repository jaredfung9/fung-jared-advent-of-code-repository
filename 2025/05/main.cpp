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
bool freshIngredient(shared_ptr<vector<RangePtr>> ranges, int64_t ingredientID) {
    for (long unsigned i = 0; i < ranges->size(); i++) {
        int64_t a, b;
        a = ((*ranges)[i])->first;
        b = ((*ranges)[i])->second;

        if ((a<= ingredientID) && (b>=ingredientID)) {
            return true;
        }
    }
    return false;
}

int countFreshIngredients(shared_ptr<vector<RangePtr>> ranges, string* filename) {
    ifstream file;
    file.open(*filename);
    int64_t query;
    int count = 0;
    while (!file.eof()) {
        file >> query;
        if (freshIngredient(ranges, query)) {
            count++;
        }
    }
    file.close();
    return count;
}
void printRange(shared_ptr<vector<RangePtr>> ranges) {
    for (auto it = ranges->begin(); it != ranges->end(); ++it) {
        cout << it[0]->first << ' '  << it[0]->second << '\n';
    }
}
int main() {
    string test_ranges = "inputs/test-ranges.txt";
    string test_queries = "inputs/test-queries.txt";
    string ranges = "inputs/ranges.txt";
    string queries = "inputs/queries.txt";
    shared_ptr<vector<RangePtr>> rangeVec = loadRange(&ranges);
    cout << "PART 1: " << countFreshIngredients(rangeVec, &queries) << '\n'; // PART 1: 770
}