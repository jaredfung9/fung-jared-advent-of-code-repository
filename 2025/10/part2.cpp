#include "Machine/Machine.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using std::cout, std::string, std::ifstream, std::queue, std::vector;

struct JoltageState {
    vector<int> currentJoltages;
    int buttonPresses;
    JoltageState() { buttonPresses = 0; }
    JoltageState(vector<int> _joltages, int _buttons) {
        currentJoltages = _joltages;
        buttonPresses = _buttons;
    }
};
/* Checks if all joltages are equal to 0. */
bool solvedState(vector<int> joltages) {
    for (int i = 0; i < (int) joltages.size(); i++) {
        if (joltages[i] != 0) { return false; }
    }
    return true;
}

/* Returns the joltage state as a result of pushing a button. */
vector<int> pressButton(vector<int> joltages, JoltageButton button) {
    vector<int> targetJoltages = button.getTargetJoltages();
    vector<int> newJoltages(joltages);
    for (int i = 0; i < (int) targetJoltages.size(); i++) {
        int target = targetJoltages[i];
        if (target >= (int) joltages.size()) {
            printf("ERROR: Invalid button\n");
            return newJoltages;
        }
        newJoltages[target] -= 1;
    }
    return newJoltages;
}

/* Returns true if every joltage is non-negative) */
bool validJoltage(vector<int> joltages) {
    for (int i = 0; i < (int) joltages.size(); i++) {
        if (joltages[i] < 0) { return false; }
    }
    return true;
}
/* GIVEN A MACHINE, returns the minimum number of button presses needed to solve the Joltage Requirements of the machine. */
int solveJoltages(Machine machine) {
    // BFS decision tree; try each button press; if state == 0, success.
    vector<JoltageButton> buttons = machine.getJoltageButtons();
    queue<JoltageState> buffer;
    buffer.push(JoltageState(machine.getInitJoltageState(), 0));    // Initial State
    JoltageState state;
    vector<int> currentJoltages;
    int currentPresses;
    while (!buffer.empty()) {
        state = buffer.front();
        buffer.pop();
        currentPresses = state.buttonPresses;
        currentJoltages = state.currentJoltages;
        printf("PRESSES %d STATE: ", currentPresses);
        // if (currentPresses > 2) { return 0;}
        for (int i = 0; i < (int)currentJoltages.size(); i++) {
            printf("%d ", currentJoltages[i]);
        }
        printf("\n");
        if (solvedState(currentJoltages)) {
            return currentPresses;
        } else {
            for (auto iter = buttons.begin(); iter != buttons.end(); iter++) {
                JoltageButton button = *iter;
                vector<int> appliedJoltages = pressButton(currentJoltages, button);
                if (!validJoltage(appliedJoltages)) { continue; }
                buffer.push(JoltageState(appliedJoltages, currentPresses+1));
            } 
        }
    }
    return 0;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please include a file\n";
        return -1;
    }
    ifstream file;
    file.open(argv[1]);
    string line;
    vector<Machine> machines;
    while (std::getline(file, line)) { 
        machines.push_back(Machine(line));
    }
    file.close();

    for (auto iter = machines.begin(); iter != machines.end(); iter++) {
        cout << solveJoltages(*iter) << '\n';
    }
    return 0;
}