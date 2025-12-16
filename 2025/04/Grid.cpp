#include "Grid.h"
#include <iostream>
#include <fstream>

Grid::Grid(std::string filename) {
    std::ifstream file;
    file.open(filename);
    int row_count = 0;
    map = new std::vector<std::vector<char>*>;
    std::string buffer;
    while (!file.eof()) {
        std::vector<char>* row = new std::vector<char>;
        map->push_back(row);
        file >> buffer;
        for (int i = 0; i < buffer.size(); i++) {
            row->push_back(buffer[i]);
        }
        row_count+=1;
        cols = buffer.size();
    }
    rows = row_count;
    file.close();
}

void Grid::printGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << tile(j, i);
        }
        std::cout<<'\n';
    }
}

char Grid::tile(int x, int y) {
    if (inbound(x, y)) {
        return (*(*map)[y])[x];
    }
    return 'X';
}

void Grid::set(int x, int y, char c) {
    if (inbound(x,y)) {
        (*(*map)[y])[x] = c;
    }
}
bool Grid::inbound(int x, int y) {
    return (((x >= 0) && (x < cols)) && ((y>=0)&&(y<rows)));
}