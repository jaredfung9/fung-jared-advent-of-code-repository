#include "Machine.hh"
#include <string>
#include <sstream>
#include <vector>
using std::string, std::stringstream, std::vector;

/*  Cleans token for processing.
[.##.] -> .##.
(1,2) -> 1 2
{1,2,3} -> 1 2 3
*/
std::string cleanToken(std::string token) {
    std::string clean = token.substr(1, token.size()-2);
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
int processToken(std::string token) {
    char c = token[0];
    std::string cleanTk = cleanToken(token);
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
            std::stringstream buttonVals(cleanTk);
            int x;
            while (buttonVals >> x) {
                val += 1 << x;
            }
            break;       
    }
    return val;
}

Machine::Machine(std::string line) {
            std::stringstream stm(line);
            std::string token;
            char c;
            while (stm>>token) { 
                c = token[0];
                switch(c) {
                    case '[':
                        initial_state = processToken(token);
                        break;
                    case '(':
                        indicator_buttons.push_back(processToken(token));
                        joltage_buttons.push_back(JoltageButton(token));
                        break;
                    case '{':
                        stringstream joltStream(cleanToken(token));
                        int x;
                        while (joltStream >> x) {
                            joltage_state.push_back(x);
                        }
                        break; 
                }
            }
}

void Machine::printState() {
    printf("MACHINE INDICATOR INIT: %d\nBUTTONS: ", initial_state);
    for (int i = 0; i < (int) indicator_buttons.size(); i++) {
        printf("%d ", indicator_buttons[i]);
    }
    printf("\n");
    printf("JOLTAGE STATE: ");
    for (int i = 0; i < (int) joltage_state.size(); i++) {
        printf("%d ", joltage_state[i]);
    }
    printf("\n");
    for (int i = 0; i < (int) joltage_buttons.size(); i++) {
        joltage_buttons[i].printButton();
    }
    printf("\n");
}

JoltageButton::JoltageButton(string line) {
    string token = cleanToken(line);
    stringstream strm(token);
    int x;
    while (strm >> x) {
        targetJoltages.push_back(x);
    }
}

void JoltageButton::printButton() {
    printf("JOLTAGE BUTTON: ");
    for (int i = 0; i < (int) targetJoltages.size(); i++) {
        printf("%d ", targetJoltages[i]);
    }
    printf("\n");
}