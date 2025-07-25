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
    dim.rows = _rows;
    dim.cols = _cols;

    file.clear();
    file.seekg(0, file.beg);
    
    return dim;
}

CharMatrix* readMatrixFromFile(ifstream& infile) {
    Dimensions dim = getFileDimensions(infile);
    CharMatrix* matrix = new CharMatrix(dim.rows, dim.cols);
    string buffer;
    for (int i = 0; i < dim.rows; ++i) {
        getline(infile, buffer);
        for (int j = 0; j < dim.cols; ++j) {
            (*matrix)(i, j) = buffer[j];
        }
    }
    return matrix;
}

int currentLoad(int depth, int rocks) {
    int load = 0;
    for (int i = 0; i < rocks; ++i) {
        load += depth - i;
    }
    return load;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide an input file.\n";
        return -1;
    }
    char* inputpath = argv[1];
    ifstream infile;
    infile.open(inputpath);
    
    
    CharMatrix* matrix = readMatrixFromFile(infile);
    int totalLoad = 0;
    for (int j = 0; j < matrix->getCols(); ++j) {
        int seenRocks = 0;
        for (int i = matrix->getRows() - 1; i >= 0; --i) {
            int currDepth = matrix->getRows() - i;
            char c = (*matrix)(i,j);
            if (c == 'O') {seenRocks += 1;}
            if (c == '#') {   
                totalLoad += currentLoad(currDepth - 1, seenRocks);        
                seenRocks = 0;
            }
        }
        totalLoad += currentLoad(matrix->getCols(), seenRocks);
    }
    infile.close();
    cout << "Total Load: " << totalLoad << '\n';
    infile.close();
    return 0;
}