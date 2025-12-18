#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

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
bool comp(RangePtr const& a, RangePtr const& b) {
    return a->first < b->first;
}

int64_t cardinality(int64_t a, int64_t b) {
    return (b - a) + 1;
}

int64_t countFreshRange(string* filename) {
    shared_ptr<vector<RangePtr>> ranges = loadRange(filename);
    std::sort(ranges->begin(), ranges->end(), &comp);
    auto joins = std::make_shared<vector<RangePtr>>();
    joins->push_back((*ranges)[0]);
    for (long unsigned int i = 1; i < ranges->size(); i++) {
        RangePtr prev_interval = joins->back();
        RangePtr curr_interval = (*ranges)[i];
        int64_t c_min = curr_interval->first;
        int64_t c_max = curr_interval->second;
        int64_t p_min = prev_interval->first;
        int64_t p_max = prev_interval->second;

        if ((c_min <= p_max)&&(c_min >= p_min) ){
            if ((c_min >= p_min)&&(p_max < c_max)) {
                prev_interval->second = curr_interval->second;
            } 
            else if (c_min < p_min) {
                joins->pop_back();
                joins->push_back(curr_interval);
            }
        }
        else {
            joins->push_back(curr_interval);
        }
    }
    int64_t count = 0;
    for (long unsigned int i = 0; i < joins->size(); i++) {
        RangePtr interval = (*joins)[i];
        count += cardinality(interval->first, interval->second);
    }
    return count;
}
int main() {
    string test_ranges = "inputs/test-ranges.txt";
    string test_queries = "inputs/test-queries.txt";
    string ranges = "inputs/ranges.txt";
    string queries = "inputs/queries.txt";
    shared_ptr<vector<RangePtr>> rangeVec = loadRange(&ranges);
    cout << "PART 1: " << countFreshIngredients(rangeVec, &queries) << '\n'; // PART 1: 770
    cout << "PART 2: " << countFreshRange(&ranges) << '\n'; // PART 2: 357674099117260

    /* PART 2:
    1748547211 - TOO LOW (used int64_t instead...)
    6043514507 - TOO LOW (used int64_t for cardinality...)
    326028421019275 - TOO LOW - fail case: (1,5) (0,10) <- outputting (0,5!!!)
    357674099117260 = CORRECT
    */
}