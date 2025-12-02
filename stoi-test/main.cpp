#include <iostream>
#include <fstream>
#include <string>

#include "dialSolver/dialSolver.h"
using std::string, std::ifstream, std::cout;

// PART 1
int part1() {
    int dial = 50;   // Dial's current location
    int count = 0;  // Times dial has been set to 0

    ifstream FILE;
    FILE.open("input.txt", std::fstream::in);
    string strbuffer;
    int GF = 100;   // modulo
    int x;
    while (!FILE.eof()) {
        FILE >> strbuffer;
        x = std::stoi(strbuffer) % GF;
        dial = (dial + x) % GF;
        if (dial == 0) {
            count+=1;
        }
    }
    FILE.close();
    std::cout << "PART 1: " << count << '\n';
    return 0;
}

// PART 2
/*
int solveFile(std::string INPUT) {
    DialSolver* dial = new DialSolver(50);
    std::ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    std::string strbuffer;
    int x;
    while (!FILE.eof()) {
        FILE >> strbuffer;
        x = stoi(strbuffer);
        if (x < 0) {
            dial->rotateLeft((-1)*x);
        }
        else {
            dial->rotateRight(x);
        }
        cout << strbuffer << " D: " << dial->readDial() << " C: " << dial->readCount() << '\n';
    }
    FILE.close();
    return dial->readCount();
}
*/
int mod(int n, int GF) {
    if (n >= 0) {
        return n % GF;
    }
    return GF + (n%GF);
}

int countFile(std::string INPUT) {
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    int count = 0;
    int dial = 50;
    int GF = 100;
    string strbuffer;
    int x;
    while (!FILE.eof()) {
        FILE >> strbuffer;
        x = stoi(strbuffer);
        count += abs(x / GF);
        int prev = dial;
        dial = mod(x + dial, GF);
        if (dial == 0) {
            count += 1;
        }
        else if (prev != 0) {
            if ((x < 0) && (prev < dial)) {
                count += 1;
            }
            else if ((x > 0) && (prev > dial)) {
                count += 1;
            }
        }
        //cout << x << ' ' << prev << ' ' << dial << ' ' << count << '\n';
    }
    FILE.close();
    return count;
}
int part2() {
    cout << "PART 2 TEST: \n" << countFile("input.txt") << "\n";
    return 0;
}

int main() {
    part1();
    part2();
    return 0;
}