#include <vector>
#include <string>
#include <sstream>

class JoltageButton {
    std::vector<int> targetJoltages;
    public:
    JoltageButton(std::string joltage_line);
    std::vector<int> getTargetJoltages() { return targetJoltages; }
    void printButton();
};

class Machine {
    std::vector<int> indicator_buttons;
    std::vector<JoltageButton> joltage_buttons;
    int initial_state;
    std::vector<int> joltage_state;
    public:
    Machine() { initial_state = 0; }
    Machine(std::string line);
    int getInitState() { return initial_state; }
    std::vector<int> getInitJoltageState() { return joltage_state; }
    std::vector<int> getIndicatorButtons() { return indicator_buttons; }
    std::vector<JoltageButton> getJoltageButtons() { return joltage_buttons; }
    void printState();
};