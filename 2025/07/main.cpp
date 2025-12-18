#include <iostream>
#include <fstream>

#include <string>

// Returns '1' iff a&b
char AND(char a, char b) {
    return ((a == '1') && (b == '1')) ? '1' : '0';
}
int main() {
    std::ifstream FILE;
    FILE.open("inputs/demo.txt");
    std::string buffer;
    FILE >> buffer;
    std::cout << AND('1', '1');
    std::cout << AND('1', '0');
    std::cout << AND('0', '1');
    std::cout << AND('0', '0');
    FILE.close();
}