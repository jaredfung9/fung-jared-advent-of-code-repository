#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using std::cout, std::string, std::ifstream, std::stringstream;

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
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please include a file\n";
        return -1;
    }
    cout << argv[0] << ' ' << argv[1] << '\n';
    ifstream file;
    file.open(argv[1]);
    string token;
    char c;
    int x;
    while (file>>token) { 
        c = token[0];
        x = processToken(token);
        cout << c << ' ' << x << '\n';
    }
    file.close();
}