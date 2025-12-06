#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


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

void processFile(ifstream* FILE) {
    string low;
    string upper;
    long long sum = 0;
    while (!FILE->eof()) {
        (*FILE) >> low;
        (*FILE) >> upper;
        cout << low << ' ' << upper << '\n';
        sum += countInvalidIDs(&low, &upper);
    }
    cout << sum;
}

int main() {
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    if (FILE.fail()) {
        cout << "ERROR OPENING: " << INPUT << '\n';
    }
    processFile(&FILE);
    FILE.close();
}