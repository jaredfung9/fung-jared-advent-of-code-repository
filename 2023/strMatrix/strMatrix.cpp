#include "strMatrix.hpp"
#include <iostream>
namespace strMatrix {
using std::ifstream;
using std::string;

    char** allocateMatrix(int rows, int cols) {
        char** matrix = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            char* row = new char[cols];
            matrix[i] = row;
        }
        return matrix;
    }

    char** readMatrix(string filename) {
        ifstream fstream(filename);
        string linebuffer;
        getline(fstream, linebuffer);

        int cols, rows;
        cols = linebuffer.length();
        rows = 1;
        while (getline(fstream, linebuffer)) {
            rows += 1;
        }

        char** matrix = allocateMatrix(rows,cols);
        string charbuffer;
        fstream.clear();
        fstream.seekg(0, fstream.beg);
        int j = rows - 1;
        while (getline(fstream, linebuffer)) {
            int i = 0;
            for (char c : linebuffer) {
                matrix[j][i] = c;
                i++;
            }
            j--;
        }
        return matrix;
    }
}