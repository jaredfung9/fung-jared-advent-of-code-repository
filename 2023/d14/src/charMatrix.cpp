#include "../include/charMatrix.hpp"
#include <iostream>
CharMatrix::CharMatrix(int _rows, int _cols) {
    rows = _rows;
    cols = _cols;
    matrixptr = new char*[_rows];
    for (int i = 0; i < _cols; ++i) {
        matrixptr[i] = new char[_cols];
        for (int j = 0; j < _cols; ++j) {
            matrixptr[i][j] = '0';
        }
    }
}

void CharMatrix::printMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrixptr[i][j];
        }
        std::cout << '\n';
    }
}

int CharMatrix::getRows() { return rows; }
int CharMatrix::getCols() { return cols; }