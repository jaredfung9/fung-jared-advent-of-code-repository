#include <iostream>
#include <fstream>

int main() {
    std::ifstream FILE;
    FILE.open("out", std::fstream::in);
    int count = 0;
    
    FILE.close();
}