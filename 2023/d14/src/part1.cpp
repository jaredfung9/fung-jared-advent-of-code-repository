#include "../include/charMatrix.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::ifstream, std::string;

struct Dimensions {
    int rows;
    int cols;
} typedef Dimensions;

Dimensions getFileDimensions(ifstream& file) {
    Dimensions dim;
    int _rows, _cols;
    _rows = 0;
    _cols = 0;

    string buffer;
    getline(file, buffer);
    _cols = buffer.length();
    _rows += 1;

    while (getline(file, buffer)) {
        _rows += 1;
    }
    cout << _rows << ' ' << _cols << '\n';
    return dim;
}
int main(int argc, char* argv[]) {
    cout << "Hello world: ";
    if (argc < 2) {
        cout << "Please provide an input file.\n";
        return -1;
    }
    char* inputpath = argv[1];
    ifstream infile;
    infile.open(inputpath);
    
    getFileDimensions(infile);
    infile.close();
    return 0;
}