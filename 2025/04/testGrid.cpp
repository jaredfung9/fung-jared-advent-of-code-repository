#include "Grid.h"
#include <iostream>
#include <string>
using std::cout;
int main() {
    cout << "Testing Grid Class:\n";
    std::string str = "test-input.txt";
    Grid* myGrid = new Grid(str);
    myGrid->printGrid();
}