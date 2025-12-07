#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_set>

using std::cout;
using std::ifstream;
using std::string;

string INPUT = "inputs/input.txt";
long generateID(int half, int exp) {
    return half + std::pow(10, exp) * half;
}

bool isInvalidID(int ID, int low, int upper) {
    return (ID >= low) && (ID <= upper);
}

int countDigits(int x) {
    return std::log10(x) + 1;
}

/* Given two std::string ptrs, LOWSTR and UPPERSTR, returns the sum from adding all invalid IDS in that range together. */
long countInvalidIDs(string* lowStr, string* upperStr) {
    long sum = 0;
    long low = stol((*lowStr));
    long upper = stol((*upperStr));
    int midpoint = lowStr->size() / 2;
    long half = 1;
    if ((lowStr->size() % 2) != 0) {
        half = pow(10,midpoint);
        midpoint++;
    } else {
        half = stol((*lowStr).substr(0, midpoint));
    }
    
    long ID = generateID(half, countDigits(half));
    while (ID <= upper) {
        if (isInvalidID(ID, low, upper)) {
            sum += ID;
        }
        half++;
        ID = generateID(half, countDigits(half));
    }
    return sum;
};

void solvePart1() {
    cout << "PART 1: ";
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    if (FILE.fail()) {
        cout << "ERROR OPENING: " << INPUT << '\n';
    }
    string low;
    string upper;
    long long sum = 0;
    while (!FILE.eof()) {
        FILE >> low >> upper;
        //cout << low << ' ' << upper << '\n';
        sum += countInvalidIDs(&low, &upper);
    }
    FILE.close();
    cout << sum << '\n';
}

/* Given a substring SUB and output string's TARGET_SIZE, returns a long ID composed of the substring repeated.
EG) (123, 6) -> 123123
    (1,5) -> 11111 
*/
long generateTestID(long SUB, int TARGET_SIZE) {
    long sum = 0;
    for (int i=0; i<TARGET_SIZE/countDigits(SUB); i++) {
        sum += SUB*pow(10,countDigits(SUB)*i);
    }
    return sum;
}

long long testTargetSize(long LOW, long UPPER, int TARGET_SIZE, std::unordered_set<long>*SEEN) {
    long long sum = 0;
    for (int i = 1; i <= TARGET_SIZE/2; i++) {
        for (long sub = pow(10,i-1); sub < pow(10,i); sub++) {
            
            long testID = generateTestID(sub, TARGET_SIZE);
            
            if ((testID >= LOW) && (testID <= UPPER)) {
                if (SEEN->count(testID) > 0) {
                    continue;
                }
                SEEN->insert(testID);
                sum += testID;
                //cout << " MATCH: " << testID << " SUBSTRING: " << sub << " TARGET: " << TARGET_SIZE << " SEEN: " << SEEN.count(testID) << " CURRENT SUM: " << sum << '\n';
            }
        }
    }
    return sum;
}
long long sumRange(string* LOW, string* UPPER, std::unordered_set<long>*SEEN) {
    long long sum = 0;
    long lowL = stol(*LOW);
    long upperL = stol(*UPPER);
    int size = LOW->size();
    while (size <= UPPER->size()) {
        sum += testTargetSize(lowL, upperL, size, SEEN);
        size++;
    }
    return sum;
}
void solvePart2() {
    cout << "PART 2: ";
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    if (FILE.fail()) {
        cout << "ERROR OPENING: " << INPUT << '\n';
    }
    string low, upper;
    long long sum = 0;
    std::unordered_set<long> SEEN; // Check that Invalid ID is not double counted between ranges.
    while (!FILE.eof()) {
        FILE >> low >> upper;
        cout << '\n' << low << ' ' << upper << '\n';
        sum += sumRange(&low, &upper, &SEEN);
        cout << "GRAND SUM: " << sum << '\n';
    }
    cout << sum << '\n';
}
int main() {
    solvePart1();
    solvePart2();
    
}

/* PART 2:
INCORRECT: 46782612412 (HIGH)
TEST: 46666175279 
Substrings only need to check while SUB.size() <= STR.size()/2.
Check if STR.size() % SUB.size() == 0 before iterating through.//

Considerations:
Can we identify IDs we can skip? How can we differentiate between 11111 and 12345?
123412 vs 123123

123123 300000
build through 1's // break ea section if an invalid is > UPPER
build through 2's
build through 3's

Maybe instead of iterating through all possible IDs, we build a "generator?"
Start at lower and try to build a test string up from each substring possible.
Then check if this string is in range.

111
1
10
100

1212
12
12*100

121212
12*10^2*0
12*10^2*1
12*10^2*2

12121212
12*10^2*0 12
12*10^2*1 1200
12*10^2*2 120000
12*10^2*3 1200000000

formula to build test ID= (STRING,int TARGET_SIZE) -> LONG
* verify TARGET_SIZE % STRING.size == 0
    i:=[0,STR.size())
        SUM for all i: SUBSTRING*10^(SUBSTRING.SIZE()*i)
    return SUM

main formula:
    read in range (LOW, UPPER)
    iterate through LOW substrings, passing appropriate SUBSTRING and TARGET_SIZE
        TODO: how to handle odd low and even upper, TARGET_SIZE changes.
        generate testID and check against range
            * Maybe set TARGET_SIZE to LOW.size() then loop and increment TARGET_SIZE until TARGET_SIZE > HIGH.size()
        if testID > UPPER, break and continue to next substring
    break once SUBSTRING.size() > TARGET_SIZE/2.
    
TODO:
    Figure out how to feed in all substrings.
        i:=[1,SIZE/2]
        is it iterating [(10^i), (10^i+1)-1] // Can probably continue from each i when TEST > UPPER
                        [1,9] 
                        [10,99]
                        [100,999]?
eg) 
100 - 123 | 111 is a match
SUBSTRING: 1
SUB.SIZE = 1
STRING.SIZE = 3
i:=[0,3)
1*10^1*0 = 1
1*10^1*1 = 10
1*10^1*2 = 100
*/