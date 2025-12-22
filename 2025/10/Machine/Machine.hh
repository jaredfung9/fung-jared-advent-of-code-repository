#include <vector>
#include <string>
#include <sstream>


class Machine {
    std::vector<int> indicator_buttons;
    int initial_state;
    public:
    Machine() { initial_state = 0; }
    Machine(std::string line);
    int getInitState() { return initial_state; }
    std::vector<int> getIndicatorButtons() { return indicator_buttons; }
    void printState();
};