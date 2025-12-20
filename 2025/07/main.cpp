#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

using std::cout, std::ifstream, std::string, std::vector;

class Manifold {
    string beams;
    ifstream FILE;
    int splits;
    vector<int> beam_vector;
    int rowsProc;
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
        rowsProc = 0;
        for (int i = 0; i < (int) beams.length(); i++) {
            if (beams[i] == '1') {
                beam_vector.push_back(i);
            }
        }
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

    /* Checks for collisions for every beam in beam vector, removing and adding the appropriate splits to beam vector as needed. */
    int quantumUpdate() {
        if (FILE.eof()) {
            return -1;
        }
        string nextRow;
        FILE >> nextRow;
        vector<int> updates;
        for (int i = 0; i < (int) beam_vector.size(); i++) {
            int particle = beam_vector[i];
            if (nextRow[particle] == '1') {
                // Collision!
                int left = particle-1;
                int right = particle+1;
                updates.push_back(left);
                updates.push_back(right);
            } else {
                // Particle continues onward.
                updates.push_back(particle);
            }
        }
        beam_vector = updates;
        rowsProc++;
        if (beam_vector.size() > 300000) {
            cout << '\n' << rowsProc <<'\n';
            return -1;
        }
        return 0;
    }
    /* Returns the number of current timelines. */
    int getTimelines() {
        return beam_vector.size();
    }
};

void part1() {
    cout << "PART 1: ";
    Manifold model("inputs/input.txt");
    while (model.update() == 0);
    cout << model.getSplits() << "\n";
}

void part2() {
    cout << "PART 2: ";
    Manifold model("inputs/input.txt");
    while (model.quantumUpdate() == 0);
    cout << model.getTimelines() << '\n';
}
int main() {
    part1();    // PART 1: 1717
    part2();
}