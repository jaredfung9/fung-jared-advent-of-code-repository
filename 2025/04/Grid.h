#pragma once
#include <string>
#include <vector>

class Grid {
    int rows;
    int cols;
    std::vector<std::vector<char>*> *map;
    public:
    Grid(std::string);
    char tile(int x, int y);
    void set(int x, int y, char c);
    void printGrid();
    bool inbound(int x, int y);
    int getRows() {return rows;}
    int getCols() {return cols;}
};