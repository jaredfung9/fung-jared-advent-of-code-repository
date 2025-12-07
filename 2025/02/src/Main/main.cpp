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

/* BEGIN PART 1: */

/* Given an long HALF, appends HALF to generate a long of the from HALF|HALF
(123) -> 123123
*/
long generateRepeatedID(long half, int exp) {
    return half + std::pow(10, exp) * half;
}

bool isInvalidID(long ID, long low, long upper) {
    return (ID >= low) && (ID <= upper);
}

int digits(long x) {
    return std::log10(x) + 1;
}

/*  Given two std::string ptrs which indicate a range, LOWSTR and UPPERSTR, returns the sum from adding all invalid IDs in that range together. 
    Finds the first half of the LOWSTR, generates an ID by appending HALF|HALF (1234 -> 1234 1234), and then checking that ID against the range.
    We continue incrementing HALF until we reach a test ID that is greater than MAX, in which case we have finished the given range.
*/
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

    long ID = generateRepeatedID(half, digits(half));
    while (ID <= upper) {
        if (isInvalidID(ID, low, upper)) {
            sum += ID;
        }
        half++;
        ID = generateRepeatedID(half, digits(half));
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
        sum += countInvalidIDs(&low, &upper);
    }
    FILE.close();
    cout << sum << '\n';
}
/* BEGIN PART 2: */
// NOTE: Although the problem was solved by thinking of each input as a substring, the actual type is long to accomodate the large inputs.
//  The following explanations are written in terms of "strings" but are implemented numerically.

/* Given a substring SUB and output string's TARGET_SIZE, returns an ID composed of SUB repeated the appropriate # of times.
EG)     (123, 6)    ->      123123
        (1,5)       ->      11111 
*/
long genRepeatSubID(long SUB, int TARGET_SIZE) {
    long sum = 0;
    for (int i=0; i<TARGET_SIZE/digits(SUB); i++) {
        sum += SUB*pow(10,digits(SUB)*i);
    }
    return sum;
}

/* Given a range from MIN to MAX, and the TARGET_SIZE of each valid ID,
Iterates through possible substrings, constructing test IDs with TARGET_SIZE and checking them against the range.
Returns the sum of all invalid IDs.
*/
long long sumTargetSize(long MIN, long MAX, int TARGET_SIZE, std::unordered_set<long>*SEEN) {
    long long sum = 0;
    // i := substring size
    for (int i = 1; i <= TARGET_SIZE/2; i++) {                          // Iterate through substring_sizes
        for (long sub = pow(10,i-1); sub < pow(10,i); sub++) {          // Iterate through substring range
            /* substring size | substring range
                i | [10^i-1, 10^i)
                1 | [1,10)
                2 | [10,100)
                3 | [100,1000)
                ...
            */
            long testID = genRepeatSubID(sub, TARGET_SIZE);
            if ((testID >= MIN) && (testID <= MAX)) {
                if (SEEN->count(testID) == 0) {                         // If this ID has not been added to our GRAND SUM yet, add it to the hashmap & GRAND SUM.
                    SEEN->insert(testID);
                    sum += testID;
                }
            }
        }
    }
    return sum;                                                         // This is the sum of all invalidIDs of given TARGET_SIZE found in the given range.
}

long long sumRange(long MIN, long MAX, std::unordered_set<long>*SEEN) {
    long long sum = 0;              
    int size = digits(MIN);
    while (size <= digits(MAX)) {                                     // Iterate through possible string sizes [MIN->size(), HIGH->size()]
        sum += sumTargetSize(MIN, MAX, size, SEEN);
        size++;
    }
    return sum;                                                         // This is the sum of all invalidIDs found in the given range.
}

void solvePart2() {
    cout << "PART 2: ";
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    if (FILE.fail()) {
        cout << "ERROR OPENING: " << INPUT << '\n';
    }
    string MIN, MAX;
    long long sum = 0;
    std::unordered_set<long> SEEN;                                      // Check that Invalid ID is not double counted between ranges.
    while (!FILE.eof()) {
        FILE >> MIN >> MAX;
        sum += sumRange(stol(MIN), stol(MAX), &SEEN);
    }
    cout << sum << '\n';                                                // OUTPUT: Grand sum (sum of all invalid IDs across all ranges).
}

int main() {
    solvePart1();
    solvePart2();
    
}

/* PART 2 BRAINSTORM:
INCORRECT: 46782612412 (HIGH)       // was double counting invalid IDs that appeared in different ranges (eg, something like 222222 was counted twice)
TEST: 46666175279 (CORRECT!)        

Substrings only need to check while SUB.size() <= STR.size()/2.
Check if STR.size() % SUB.size() == 0 before iterating through.//

Considerations:
Can we identify IDs we can skip? How can we differentiate between 11111 and 12345?
123412 vs 123123

123123 300000
build through 1's // break ea section if an invalid is > MAX
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
    read in range (MIN, MAX)
    iterate through MIN substrings, passing appropriate SUBSTRING and TARGET_SIZE
        TODO: how to handle odd low and even upper, TARGET_SIZE changes.
        generate testID and check against range
            * Maybe set TARGET_SIZE to MIN.size() then loop and increment TARGET_SIZE until TARGET_SIZE > HIGH.size()
        if testID > MAX, break and continue to next substring
    break once SUBSTRING.size() > TARGET_SIZE/2.
    
TODO:
    Figure out how to feed in all substrings.
        i:=[1,SIZE/2]
        is it iterating [(10^i), (10^i+1)-1] // Can probably continue from each i when TEST > MAX
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