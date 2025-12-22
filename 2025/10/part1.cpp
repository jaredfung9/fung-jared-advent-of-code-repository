#include "Machine/Machine.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using std::cout, std::string, std::ifstream, std::queue, std::vector;

/* Represents the state of a Machine after N buttonPresses. */
struct State {
    int currentState;
    int buttonPresses;
};

void printState(State s) {
    printf("State: %d : Presses: %d\n", s.currentState, s.buttonPresses);
}

/* Given a MACHINE, returns the minimum number of button presses needed to solve the machine. */
int solveMachine(Machine machine) {
    // BFS decision tree; try each button press
    vector<int> buttons = machine.getIndicatorButtons();
    queue<State> buffer;
    buffer.push(State{machine.getInitState(), 0});
    State state;
    int currState, currPresses;
    while (!buffer.empty()) {
        state = buffer.front();
        buffer.pop();
        currState = state.currentState;
        currPresses = state.buttonPresses;
        if (currState == 0) {   // Solved position
            return currPresses; 
        }
        // Otherwise, from the current state, try pressing each button.
        for (int i = 0; i < (int) buttons.size(); i++) {
            int button = buttons[i];
            buffer.push(State{currState^button, currPresses+1});
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

    int count = 0;
    for (auto iter = machines.begin(); iter != machines.end(); iter++) {
        count += solveMachine(*iter);
    }
    printf("PART 1: %d\n", count);  // 434
    return 0;
}