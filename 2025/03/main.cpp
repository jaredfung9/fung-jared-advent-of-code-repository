#include <iostream> // input-output
#include <string> 
#include <fstream> // file
#include <cstdint> // integer type defintions
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
typedef std::array<std::array<int64_t, MAX_BATTERIES>, MAX_BANK_SIZE> bankArray;
void printMap(bankArray* map) {
    for (int i = 0; i < map->size(); i++) {
        for (int j = 0; j < (*map)[i].size(); j++) {
            cout << ((*map)[i])[j] << ' ';
        }
        cout << '\n';
    }
}
int64_t largestGigaJolt(string* bankStr) {
    using std::array;
    bankArray map;    // maps (int INDEX, int BATTERIES) -> (int64_t) LARGEST_BATT_COMBO
    for (int i = 0; i < map.size(); i++) {
        map[i].fill(-1);
    } // initialize each value to -1
    printMap(&map);
    for (int batt = 1; batt <= 12; batt++) {}
}
int main() {
    cout << "PART 1: " << processFile("input.txt") << '\n'; // PART 1: 17278
    string test = "3232221546315133223433433342253232332422524653333335332433322333355343313233335255322525232232347253";
    largestGigaJolt(&test);
}