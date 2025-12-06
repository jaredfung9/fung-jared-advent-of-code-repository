#include "main.h"
#include <iostream>
#include <fstream>
#include <string>


using std::cout;
using std::ifstream;
using std::string;

string INPUT = "inputs/input.txt";

int main() {
    ifstream FILE;
    FILE.open(INPUT, std::fstream::in);
    if (FILE.fail()) {
        cout << "ERROR OPENING: " << INPUT << '\n';
    }
    string foo;
    string bar;
    FILE >> foo;
    FILE >> bar;
    
    cout << foo << ' ' << bar << '\n';
    cout << "SIZES: " << foo.size() << ' ' << bar.size() << '\n';
    
    FILE >> foo;
    FILE >> bar;
    
    cout << foo << ' ' << bar << '\n';
    cout << "SIZES: " << foo.size() << ' ' << bar.size() << '\n';
    FILE.close();
}