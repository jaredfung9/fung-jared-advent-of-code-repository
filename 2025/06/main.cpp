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

void part1() {
ifstream FILE;
    // Load terms into memory
    FILE.open(NUMINPUT);
    vector<shared_ptr<stack<int>>> memory_bank;
    string buffer;

    while (std::getline(FILE, buffer)) {
        istringstream buffer_stream (buffer);
        auto mem_row = std::make_shared<stack<int>>();
        memory_bank.push_back(mem_row);
        int x = 0;
        while (!buffer_stream.eof()) {
            buffer_stream >> x;
            mem_row->push(x);
        }
    }
    FILE.close();
    // Process Operations
    FILE.open(OPINPUT);
    stack<char> ops;
    while (!FILE.eof()) {
        char x;
        FILE >> x;
        ops.push(x);
    }
    FILE.close();

    int64_t total = 0;
    int64_t product = 1;
    int64_t sum = 1;
    while (!ops.empty()) {
        char c = ops.top();
        ops.pop();
        switch (c) {
            case '*':
                product = 1;
                for (unsigned long i = 0; i < memory_bank.size(); i++) {
                    if (!memory_bank[i]->empty()) {
                        cout << memory_bank[i]->size() << ' ';
                        product *= memory_bank[i]->top();
                        memory_bank[i]->pop();
                    }
                }
                cout << "=" << product << '\n';
                total += product;
            case '+':
                sum = 0;
                for (unsigned long i = 0; i < memory_bank.size(); i++) {
                    if (!memory_bank[i]->empty()) {
                        cout << memory_bank[i]->size() << ' ';
                        sum += memory_bank[i]->top();
                        memory_bank[i]->pop();
                    }
                }
                cout << "=" << sum << '\n';
                total += sum;
        }
    }
    
    cout << total << '\n';
}

int main() {
    part1();
}    