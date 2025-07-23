#include <iostream>
#include "charMatrix.hpp"

int main() {
    CharMatrix* matrix = new CharMatrix(6,5);
    std::cout << "Rows: " << matrix->getRows() <<'\n';
    std::cout << "Cols: " << matrix->getCols() <<'\n';
    std::cout << "Init: " << (*matrix)(1,2) << "\n";
    (*matrix)(1,2) = 'a';
    std::cout << "Post: " << (*matrix)(1,2) << '\n';
}