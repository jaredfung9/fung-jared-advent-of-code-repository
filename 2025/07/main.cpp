#include <iostream>
#include <fstream>

#include <string>

// Returns '1' iff a&b
char AND(char a, char b) {
    return ((a == '1') && (b == '1')) ? '1' : '0';
}

char OR(char a, char b) {
    return ((a == '1') || (b == '1')) ? '1' : '0';
}

char XOR(char a, char b) {
    return (((a == '1') || (b == '1'))&&(a != b)) ? '1' : '0';
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
    std::cout <<'\n';
    std::cout << OR('1', '1');
    std::cout << OR('1', '0');
    std::cout << OR('0', '1');
    std::cout << OR('0', '0');
    std::cout <<'\n';
    std::cout << XOR('1', '1');
    std::cout << XOR('1', '0');
    std::cout << XOR('0', '1');
    std::cout << XOR('0', '0');
    FILE.close();
}