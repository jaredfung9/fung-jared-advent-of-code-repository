#include <vector>
#include <string>
#include <sstream>


class Machine {
    std::vector<int> buttons;
    int initial_state;
    public:
    Machine() { initial_state = 0; }
    Machine(std::string line);
    int getInitState() { return initial_state; }
    std::vector<int> getButtons() { return buttons; }
    void printState();
};