#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
// char AND(char a, char b) {
//     return ((a == '1') && (b == '1')) ? '1' : '0';
// }

// char OR(char a, char b) {
//     return ((a == '1') || (b == '1')) ? '1' : '0';
// }

// char XOR(char a, char b) {
//     return (((a == '1') || (b == '1'))&&(a != b)) ? '1' : '0';
// }

using std::cout, std::ifstream, std::string;

class Manifold {
    string beams;
    ifstream FILE;

    /* Returns a string representing the positions where a beam from BEAMS collided with a splitter in the NEXTROW. 
    Returns NULL upon failure to compare the two rows. */
    string calculateCollisions(string nextRow) {
        if (nextRow.size() != beams.size()) {
            cout << "ERROR: rowsizes do not match (nextRow, beams): " << nextRow.size() << ' ' << beams.size() <<'\n';
            return NULL;
        }
        string collisions(beams.size(), '0');
        for (unsigned int i = 0; i < beams.size(); i++) {
            if ((nextRow[i] == '1') && (beams[i] == '1')) {
                collisions[i] = '1';
            }
        }
        return collisions;
    }
    public:
    Manifold(string filename) {
        FILE.open(filename);
        FILE >> beams;
    }
    ~Manifold() {
        FILE.close();
    }
    void printBeams() {
        cout << beams << '\n';
    }
    /* Updates the location of beams by checking the next row for splitters. */
    void update() {
        string nextRow;
        FILE >> nextRow;
        string collisions = calculateCollisions(nextRow);
        cout << collisions << '\n';
    }
};
int main() {
    string input = "inputs/demo.txt";
    Manifold model("inputs/demo.txt");
    model.printBeams();
    model.update();
    model.update();
}