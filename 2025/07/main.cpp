#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
// char AND(char a, char b) {
//     return ((a == '1') && (b == '1')) ? '1' : '0';
// }

// char OR(char a, char b) {
//     return ((a == '1') || (b == '1')) ? '1' : '0';
// }

// char XOR(char a, char b) {
//     return (((a == '1') || (b == '1'))&&(a != b)) ? '1' : '0';
// }

using std::cout, std::ifstream, std::string;
const int BIT_WIDTH = 64;
class Manifold {
    int width;
    int64_t beams;
    ifstream FILE;
    public:
        Manifold(string filename) {
            FILE.open(filename);
            string buffer;
            if (!FILE.eof()) {
                FILE >> buffer;
                width = buffer.size();
                beams = std::stoi(buffer, nullptr, 2);
            }
        }
        ~Manifold() {
            FILE.close();
        }

        void printBeams() {
            string s = std::bitset< 64 > (beams).to_string();
        }
};
int main() {
    Manifold model("inputs/demo.txt");
}