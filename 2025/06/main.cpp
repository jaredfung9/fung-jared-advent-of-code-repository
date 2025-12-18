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

shared_ptr<stack<char>> loadOps(string* filename) {
    ifstream FILE;
    FILE.open(*filename);
    string buffer;
    std::getline(FILE, buffer);
    istringstream buffer_stream (buffer);
    auto _stack = std::make_shared<stack<char>>();
    char x;
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
char tapc(shared_ptr<stack<char>> _stack) {
    char c = _stack->top();
    _stack->pop();
    return c;
}

// returns the sum of the top of each bank.
int64_t sumBanks(vector<shared_ptr<stack<int>>>* banks) {
    int64_t sum = 0;
    for (unsigned long i = 0; i < banks->size(); i++) {
        sum += tapi((*banks)[i]);
    }
    return sum;
}
// returns the product of the top of each bank.
int64_t mulBanks(vector<shared_ptr<stack<int>>>* banks) {
    int64_t prod = 1;
    for (unsigned long i = 0; i < banks->size(); i++) {
        prod *= tapi((*banks)[i]);
    }
    return prod;
}
void part1() {
    shared_ptr<stack<char>> ops = loadOps(&OPINPUT);
    cout << "Loaded Ops: " << ops->size() << '\n';
    
    // Load in num banks
    ifstream FILE;
    FILE.open(NUMINPUT);
    vector<shared_ptr<stack<int>>> banks;
    while (!FILE.eof()) {
        string buffer;
        std::getline(FILE, buffer);
        banks.push_back(loadMemoryRow(&buffer));
    }
    FILE.close();
    for (unsigned int i = 0; i < banks.size(); i++) {
        cout << banks[i]->size() << '\n';
    }
    cout << ops->size() << '\n';
    int64_t total = 0;
    int64_t calc = 0;
    while (!ops->empty()) {
        char c = tapc(ops);
        switch (c) {
            case '*':
                calc = mulBanks(&banks);
                break;
            case '+':
                calc = sumBanks(&banks);
                break;
        }
        total += calc;
        cout << calc << '\n';
        cout.flush();
    }
    cout << "PART 1: " << total << '\n';
}

int main() {
    part1();
}    