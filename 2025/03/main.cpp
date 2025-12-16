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
    std::unordered_map<string*, int64_t>* maps[MAX_BATTERIES];
    public:
    batteryMap() {
        for (int i = 0; i < MAX_BATTERIES; i++) {
            maps[i] = new std::unordered_map<string*, int64_t>;
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
        (*maps[batteries-1])[str] = val;
    }
    int64_t lookup(string* str, int batteries) {
        if (batteries > MAX_BATTERIES) {
            return -1;
        }
        auto result = maps[batteries-1]->find(str);
        if (result != maps[batteries-1]->end()) {
            return result->second;
        }
        return -1;
    }
};

int64_t concatInt(int64_t l, int64_t r, int batteries) {
    return l*pow(10,batteries-1) + r;
}
int main() {
    cout << "PART 1: " << processFile("input.txt") << '\n'; // PART 1: 17278
    batteryMap* myMap = new batteryMap();
    int64_t _val1 = 12;
    int64_t _val2 = 3;
    string _str = "123";
    myMap->store(&_str,1, _val1);
    myMap->store(&_str,2, _val2);
    int64_t look1 = myMap->lookup(&_str, 1);
    int64_t look2 = myMap->lookup(&_str, 2);
    int64_t look3 = myMap->lookup(&_str, 3);

    string sub1 = _str.substr(0,1);
    string sub2 = _str.substr(1);
    cout << "TEST:\n" << look1 << ' ' << look2 << ' ' << look3 <<'\n';
    cout << sub1 << ' ' << sub2 << ' ' << concatInt(stoi(sub1), stoi(sub2), 3);
}