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
    string x;
    while (buffer_stream >> x) {
        cout << x << ' ';
        _stack->push(x);
    }
    FILE.close();
    return _stack;
}

shared_ptr<stack<int>> loadMemoryRow(string* input_row) {
    istringstream buffer_stream (*input_row);
    auto _stack = std::make_shared<stack<int>>();
    int x;
    while (buffer_stream >> x) {
        cout << x << ' ';
        _stack->push(x);
    }
    cout << '\n';
    return _stack;
}

// Top and Pop int from stack
int tapi(shared_ptr<stack<int>> _stack) {
    int x = _stack->top();
    _stack->pop();
    return x;
}

// Top and Pop char from stack
int tapc(shared_ptr<stack<char>> _stack) {
    char c = _stack->top();
    _stack->pop();
    return c;
}

void part1() {
    shared_ptr<stack<string>> ops = loadOps(&OPINPUT);
    cout << "Loaded Ops: " << ops->size() << '\n';

    //const int BANKS = 3;
    
    ifstream FILE;
    FILE.open(NUMINPUT);
    vector<shared_ptr<stack<int>>> banks;
    while (!FILE.eof()) {
        string buffer;
        std::getline(FILE, buffer);
        banks.push_back(loadMemoryRow(&buffer));
    }
    FILE.close();
}

int main() {
    part1();
}    