#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using std::cout, std::string, std::ifstream, std::stringstream, std::queue, std::vector;

/*  Cleans token for processing.
    [.##.] -> .##.
    (1,2) -> 1 2
    {1,2,3} -> 1 2 3
*/
string cleanToken(string token) {
    string clean = token.substr(1, token.size()-2);
    for (int i = 0; i < (int) clean.size(); i++) {
        if (clean[i] == ',') {
            clean[i] = ' ';
        }
    }
    return clean;
}
/* Given a token that represents:
machine-state: [.###.] -> int initial_state
button: (0,1,2) -> int bitmask
joltages" {12} -> -1
*/
int processToken(string token) {
    char c = token[0];
    string cleanTk = cleanToken(token);
    int val = 0;
    switch(c) {
        case '{':
            val = -1;  // IE do nothing
            break;
        case '[':
            for (int i = 0; i < (int) cleanTk.size(); i++) {
                if (cleanTk[i] == '#') {
                    val += 1 << i;
                }
            }
            break;
        case '(': 
            stringstream buttonVals(cleanTk);
            int x;
            while (buttonVals >> x) {
                val += 1 << x;
            }
            break;       
    }
    return val;
}
class Machine {
    vector<int> buttons;
    int initial_state;
    public:
    Machine() {
        initial_state=0;
    }
    Machine(string line) {
        stringstream stm(line);
        string token;
        char c;
        while (stm>>token) { 
            c = token[0];
            switch(c) {
                case '[':
                    initial_state = processToken(token);
                    break;
                case '(':
                    buttons.push_back(processToken(token));
                    break;
                case '{':
                    break;  // Ignore joltages
            }
        }
    }
    int initialState() {
        return initial_state;
    }
    vector<int> retrieveButtons() {
        return buttons;
    }
    void printState() {
        printf("MACHINE INIT: %d BUTTONS: ", initial_state);
        for (int i = 0; i < (int) buttons.size(); i++) {
            printf("%d ", buttons[i]);
        }
        printf("\n");
    }
};

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
    vector<int> buttons = machine.retrieveButtons();
    queue<State> buffer;
    buffer.push(State{machine.initialState(), 0});
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
    printf("PART 1: %d\n", count);
}