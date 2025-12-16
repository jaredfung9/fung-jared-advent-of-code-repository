#include <iostream> // input-output
#include <string> 
#include <fstream> // file
#include <cstdint> // integer type defintions
#include <cmath>
#include <algorithm>
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

int main() {
    cout << "PART 1: " << processFile("input.txt") << '\n'; // PART 1: 17278
}