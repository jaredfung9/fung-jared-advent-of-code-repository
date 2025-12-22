#include <iostream>
#include <fstream>
#include <string>
using std::cout, std::string, std::ifstream;

int processToken(string token) {
    return 0;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please include a file\n";
        return -1;
    }
    cout << argv[0] << ' ' << argv[1] << '\n';
    ifstream file;
    file.open(argv[1]);
    string buffer;
    while (file>>buffer) { cout << buffer << '\n'; }
    file.close();
}