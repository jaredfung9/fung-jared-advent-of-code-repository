#include "Machine/Machine.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using std::cout, std::string, std::ifstream, std::queue, std::vector;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please include a file\n";
        return -1;
    }
    ifstream file;
    file.open(argv[1]);
    string line;
    vector<Machine> machines;
    while (std::getline(file, line)) { 
        machines.push_back(Machine(line));
    }
    file.close();

    for (auto iter = machines.begin(); iter != machines.end(); iter++) {
        iter->printState();
    }
    return 0;
}