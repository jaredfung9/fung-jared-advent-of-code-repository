#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
typedef struct {
    int64_t first;
    int64_t second;
}Range;

std::vector<Range>* loadRange(std::string* filename) {
    std::ifstream file;
    file.open(*filename);
    std::vector<Range>* ranges = new std::vector<Range>;
    int64_t a, b;
    while (!file.eof()) {
        file >> a >> b;
        std::cout << a << ' ' << b << '\n';
    }
    file.close();
    return ranges;
}
int main() {
    std::string input = "inputs/test-ranges.txt";
    loadRange(&input);
}