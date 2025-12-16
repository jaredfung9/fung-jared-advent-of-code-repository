#include <iostream> // input-output
#include <string> 
#include <fstream> // file
#include <cstdint> // integer type defintions
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <array>
/* Remember, max value depends on number of bits && whether the value is signed. 2^(b)-1 gives the maximum value for an unsigned int.
For signed values: range calculations MIN:= -2^(b-1)-1 and MAX:= 2^(b-1)-1; the CARDINALITY OF THE ENTIRE RANGE is always = 2^b =
|negative vals| + 1 + |positive vals| */

const int MAX_BATTERIES = 12;
const int MAX_BANK_SIZE = 100;

using std::string, std::cout, std::ifstream;
string DEMO_STRING = "987654321111111";

int ctoi(char c) {
    return int(c) - 48;
}

int largestJolt(string* bankStr) {
    int largest = 0;
    for (int i = 0; i < bankStr->length(); i++) {
        int tens = ctoi(bankStr->at(i)) * 10;
        for (int j = i+1; j < bankStr->length(); j++) {
            int ones = ctoi(bankStr->at(j));
            if (tens + ones> largest) {
                largest = tens + ones;
            }
        }
    }
    return largest;
}

int processFile(const char* filename) {
    ifstream FILE;
    FILE.open(filename);
    string input;
    int total = 0;
    while (!FILE.eof()) {
        FILE >> input;
        total += largestJolt(&input);
    }
    FILE.close();
    return total;
}

class batteryMap {
    std::unordered_map<string, int64_t>* maps[MAX_BATTERIES];
    public:
    batteryMap() {
        for (int i = 0; i < MAX_BATTERIES; i++) {
            maps[i] = new std::unordered_map<string, int64_t>;
        }
    }
    ~batteryMap() {
        for (int i = 0; i <MAX_BATTERIES; i++) {
            delete maps[i];
        }
    }
    void store(string* str, int batteries, int64_t val) {
        if (batteries > MAX_BATTERIES) {
            return;
        }
        (*maps[batteries-1])[*str] = val;
    }
    int64_t lookup(string* str, int batteries) {
        if (batteries > MAX_BATTERIES) {
            return -1;
        }
        auto result = maps[batteries-1]->find(*str);
        if (result != maps[batteries-1]->end()) {
            return result->second;
        }
        return -1;
    }
};

int64_t concatInt(int64_t l, int64_t r, int batteries) {
    return batteries == 1 ? l : l*pow(10,batteries-1) + r;
}

int64_t max(int64_t a, int64_t b) {
    return a > b ? a : b;
}
/* Calculates the largestCombo of a given bank, stores results in map, and returns the value.*/
int64_t largestCombo(batteryMap* map, string* str, int batteries) {
    if (batteries <= 0) {
        return 0;
    }

    if (map->lookup(str, batteries) != -1) {
        return map->lookup(str, batteries);
    } 
    else {
        if (str->size() == 1 ) {
            return ctoi(str->at(0));
        }
        string sub = str->substr(1);
        int64_t a = concatInt(ctoi(str->at(0)), largestCombo(map, &sub, batteries-1), batteries);
        int64_t b = largestCombo(map, &sub, batteries);
        map->store(str, batteries, max(a,b));
        return map->lookup(str, batteries);
    }
}

/* Fills out batteryMap starting from combos of a single battery all the way to combos of MAX_BATTERIES. */
int64_t largestGigaJolt(string* str) {
    batteryMap* map = new batteryMap();
    for (int batt = 1; batt <= MAX_BATTERIES; batt++) {
        for (int i = str->size()-1; i >= 0; i--) {
            string sub = str->substr(i);
            largestCombo(map, &sub, batt);
        }
    }
    
    int64_t val = map->lookup(str,MAX_BATTERIES);
    delete map;
    cout << *str << ' ' << val << '\n';
    return val;
}

int64_t processFile2(const char* filename) {
    std::ifstream file;
    file.open(filename);
    string input;
    int64_t total = 0;
    while (!file.eof()) {
        file >> input;
        total += largestGigaJolt(&input);
    }
    file.close();
    return total;
}
int main() {
    cout << "PART 1:\n" << processFile("input.txt") << '\n'; // PART 1: 17278
    //cout << "PART 2:\n" << processFile2("test-input.txt") << '\n';
    string mystr = "987654321111111";
    cout << largestGigaJolt(&mystr) << '\n';
}