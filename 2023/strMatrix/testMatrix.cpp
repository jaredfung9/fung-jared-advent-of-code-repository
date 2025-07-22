#include "strMatrix.hpp"
#include <string>
#include <iostream> 
int main() {
    std::string filename = "test1.in";
    char** matrix = strMatrix::readMatrix(filename);
    std::cout << "matrix: " << matrix[0][3];
    return 0;
}