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

shared_ptr<stack<string>> loadStackFromLine(string* buffer) {
    istringstream buffer_stream (*buffer);
    auto _stack = std::make_shared<stack<string>>();
    while (!buffer_stream.eof()) {
        string x;
        buffer_stream >> x;
        _stack->push(x);
    }
    return _stack;
}

void part1() {
    ifstream FILE;
    FILE.open(OPINPUT);
    string buffer;
    std::getline(FILE,buffer);
    cout << "INPUT: " << buffer << '\n';
    shared_ptr<stack<string>> ops = loadStackFromLine(&buffer);
    cout << ops->size();
    FILE.close();
}

int main() {
    
    part1();
}    