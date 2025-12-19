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
    int splits;
    /* Returns a string representing the positions where a beam from BEAMS collided with a splitter in the NEXTROW. 
    Returns NULL upon failure to compare the two rows. */
    string calculateCollisions(string nextRow) {
        if (nextRow.length() != beams.length()) {
            cout << "ERROR: rowsizes do not match (nextRow, beams): " << nextRow.size() << ' ' << beams.size() <<'\n';
            return NULL;
        }
        string collisions(beams.length(), '0');
        for (int i = 0; i < (int) beams.length(); i++) {
            if ((nextRow[i] == '1') && (beams[i] == '1')) {
                collisions[i] = '1';
            }
        }
        return collisions;
    }
    /* Given a string representing all the collisions, updates BEAMS to reflect split beams. */
    void applyCollisions(string collisions) {
        if (collisions.length() != beams.length()) {
            cout << "ERROR: rowsizes do not match (collision, beams): " << collisions.length() << ' ' << beams.size() << '\n';
            return;
        }
        for (unsigned int i = 0; i < beams.length(); i++) {
            if (collisions[i] == '1') {
                splits++;
                beams[i] = '0';
                int left_indice = i-1;
                int right_indice = i+1;
                if ((left_indice >= 0) && (left_indice < (int) beams.length())) {
                    beams[left_indice] = '1';
                }
                if ((right_indice >= 0) && (right_indice < (int) beams.length())) {
                    beams[right_indice] = '1';
                }
            }
            
        }
    }
    public:
    Manifold(string filename) {
        FILE.open(filename);
        FILE >> beams;
        splits = 0;
    }
    ~Manifold() {
        FILE.close();
    }
    void printBeams() {
        cout << beams << '\n';
    }
    /* Returns the number of beams in the current beam row. */
    int getSplits() {
        return splits;
    }
    /* Updates the location of beams by checking the next row for splitters.
    Returns 0 if operation was successful, -1 otherwise. */
    int update() {
        if (FILE.eof()) {
            return -1;
        }
        string nextRow;
        FILE >> nextRow;
        string collisions = calculateCollisions(nextRow);
        applyCollisions(collisions);
        // printBeams();
        return 0;
    }
};
void part1() {
    cout << "PART 1: ";
    Manifold model("inputs/input.txt");
    while (model.update() == 0);
    cout << model.getSplits() << "\n";
}
int main() {
    part1();    // PART 1: 1717
}