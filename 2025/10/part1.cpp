#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
using std::cout, std::string, std::ifstream, std::stringstream, std::stack, std::vector;

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
    void setInit(int init) {
        initial_state = init;
    }
    void addButton(int button) {
        buttons.push_back(button);
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
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please include a file\n";
        return -1;
    }
    ifstream file;
    file.open(argv[1]);
    string token;
    char c;
    vector<Machine> machines;
    Machine machine;    // Sentinel Node
    while (file>>token) { 
        c = token[0];
        switch(c) {
            case '[':
                machines.push_back(machine);
                machine = Machine();
                machine.setInit(processToken(token));
                break;
            case '(':
                machine.addButton(processToken(token));
                break;
            case '{':
                break;
        }
    }
    machines.push_back(machine); // Make sure to add the final machine
    machines.erase(machines.begin()); // Erase the sentinel node
    for (auto iter = machines.begin(); iter != machines.end(); iter++) {
        iter->printState();
    }
    file.close();
}