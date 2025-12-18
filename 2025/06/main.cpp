#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

#include <cstdint>

using std::cout, std::ifstream, std::vector, std::stack, std::string, std::istringstream, std::shared_ptr;

string INPUT = "inputs/nums.txt";
int main() {
    ifstream FILE;
    FILE.open(INPUT);
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

    shared_ptr<stack<int>> dummy = memory_bank[0];
    while (!dummy->empty()) {
        cout << dummy->top() << '\n';
        dummy->pop();
    }
    FILE.close();
}