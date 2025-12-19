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

class Manifold {
    string beams;
    ifstream FILE;
    public:
    Manifold(string filename) {
        FILE.open(filename);
        FILE >> beams;
    }
    ~Manifold() {
        FILE.close();
    }
    void printBeams() {
        cout << beams << '\n';
    }
};
int main() {
    string input = "inputs/demo.txt";
    Manifold model("inputs/demo.txt");
    model.printBeams();
}