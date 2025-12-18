#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

#include <cstdint>

using std::cout, std::ifstream, std::vector, std::stack, std::string, std::istringstream, std::shared_ptr;

string NUMINPUT = "inputs/test-nums.txt";
string OPINPUT = "inputs/test-ops.txt";

shared_ptr<stack<string>> loadOps(string* filename) {
    ifstream FILE;
    FILE.open(*filename);
    string buffer;
    std::getline(FILE, buffer);
    istringstream buffer_stream (buffer);
    auto _stack = std::make_shared<stack<string>>();
    while (!buffer_stream.eof()) {
        string x;
        buffer_stream >> x;
        cout << x << ' ';
        _stack->push(x);
    }
    FILE.close();
    return _stack;
}

void part1() {
    shared_ptr<stack<string>> ops = loadOps(&OPINPUT);
    cout << "Loaded Ops: " << ops->size() << '\n';
}

int main() {
    
    part1();
}    