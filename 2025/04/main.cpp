#include <iostream>
#include <string>
#include "Grid.h"

bool isRoll(Grid* grid, int x, int y) {
    return grid->tile(x, y) == '@';
}
bool accessibleRoll(Grid* grid, int x, int y) {
    int rollCount = 0;
    for (int i = y-1; i <= y+1; i++) {
        for (int j = x-1; j <= x+1; j++) {
            if ((i==y)&&(j==x)) {
                continue;
            }
            if (grid->tile(j,i) == '@') {
                rollCount++;
            }
        }
    }
    return (rollCount < 4);
}

int processGrid1(Grid* grid) {
    int count = 0;
    for (int row = 0; row < grid->getRows(); row++) {
        for (int col = 0; col < grid->getCols(); col++) {
            if ((grid->tile(col, row) == '@') && (accessibleRoll(grid, col, row))) {
                count += 1;
            }
        }
    }
    return count;
}

int processGrid2(Grid* grid) {
    int count = 0;
    for (int row = 0; row < grid->getRows(); row++) {
        for (int col = 0; col < grid->getCols(); col++) {
            if ((grid->tile(col, row) == '@') && (accessibleRoll(grid, col, row))) {
                count += 1;
                grid->set(col, row, '.');
            }
        }
    }
    return count;
}
int main() {
    // PART 1:
    Grid* grid = new Grid("input.txt");
    std::cout << "PART 1: " << processGrid1(grid) << '\n'; // PART 1: 1397

    // PART 2:
    Grid* grid2 = new Grid("input.txt");
    int total_count = 0;
    int count = processGrid2(grid2);
    while (count > 0) {
        total_count+=count;
        count = processGrid2(grid2);
    }
    std::cout << "PART 2: " << total_count << '\n'; // PART 2: 8758
}