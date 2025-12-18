#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <cmath>
#include <cstdint>

using std::cout, std::ifstream, std::vector, std::stack, std::string, std::istringstream, std::shared_ptr, std::pow;

shared_ptr<stack<char>> loadOps(string* filename) {
    ifstream FILE;
    FILE.open(*filename);
    string buffer;
    std::getline(FILE, buffer);
    istringstream buffer_stream (buffer);
    auto _stack = std::make_shared<stack<char>>();
    char x;
    while (buffer_stream >> x) {
        // cout << x << ' ';
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
        _stack->push(x);
    }
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
    string NUMINPUT = "inputs/nums.txt";
    string OPINPUT = "inputs/ops.txt";
    shared_ptr<stack<char>> ops = loadOps(&OPINPUT);
    // cout << "Loaded Ops: " << ops->size() << '\n';
    
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
    // for (unsigned int i = 0; i < banks.size(); i++) {
    //     cout << banks[i]->size() << '\n';
    // }
    // cout << ops->size() << '\n';
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
        // cout << calc << '\n';
        // cout.flush();
    }
    cout << "PART 1: " << total << '\n';
}

typedef shared_ptr<stack<char>> sharedStackPtr;

sharedStackPtr stoStack(string* str) {
    auto _stack = std::make_shared<stack<char>>();
    for (unsigned long i = 0; i < str->size(); i++) {
        char c = str->at(i);
        _stack->push(c);
    }
    return _stack;
}

shared_ptr<vector<sharedStackPtr>> loadBanks(string* filename) {
    ifstream FILE;
    FILE.open(*filename);
    auto banks = std::make_shared<vector<sharedStackPtr>>();
    string buffer;
    while (std::getline(FILE,buffer)) {
        banks->push_back(stoStack(&buffer));
    }
    FILE.close();
    return banks;
}
// Returns 0 if all banks returned ' ';
int64_t getTerm(shared_ptr<vector<sharedStackPtr>> banks) {
    int64_t term = 0;
    int place = 0;
    stack<int> term_stack;
    for (unsigned long i = 0; i < banks->size(); i++) {
        sharedStackPtr bank = (*banks)[i];
        char c = bank->top();
        bank->pop();
        if (c == ' ') {
            continue;
        }
        
        term_stack.push(atoi(&c));
        place += 1;
    }
    for (int i = 0; i < place; i++) {
        term += term_stack.top()*pow(10,i);
        term_stack.pop();
    }
    return term;
}
void part2() {
    string NUMINPUT = "inputs/test-nums.txt";
    string OPINPUT = "inputs/test-ops.txt";
    sharedStackPtr ops = loadOps(&OPINPUT); 
    shared_ptr<vector<sharedStackPtr>> banks = loadBanks(&NUMINPUT);
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';

    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';

    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';

    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
    cout << getTerm(banks) << '\n';
}
int main() {
    part1(); // PART 1: 7098065460541
    part2();
}    