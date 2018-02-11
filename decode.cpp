#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

queue<char> decode(char encoded) {
    queue<char> twomer;
    for (int i = 1; i >= 0; i--) {
        switch (encoded >> (4 * i) & 0xF) {
            case 0x8: twomer.push('A'); break;
            case 0x4: twomer.push('C'); break;
            case 0x2: twomer.push('G'); break;
            case 0x1: twomer.push('T'); break;
            case 0x9: twomer.push('W'); break;
            case 0x6: twomer.push('S'); break;
            case 0xC: twomer.push('M'); break;
            case 0x3: twomer.push('K'); break;
            case 0xA: twomer.push('R'); break;
            case 0x5: twomer.push('Y'); break;
            case 0x7: twomer.push('B'); break;
            case 0xB: twomer.push('D'); break;
            case 0xD: twomer.push('H'); break;
            case 0xE: twomer.push('V'); break;
            case 0xF: twomer.push('N'); break;
            default: twomer.push(0);
        }
    }
    return twomer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) throw invalid_argument("Please specify file to decode.");
    ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) throw runtime_error("Cannot open file.");

    string line;
    while (getline(file, line)) {
        for (uint i = 0; i < line.length(); i++) {
            queue<char> twomer = decode(line[i]);
            cout << twomer.front() << twomer.back();
        }
        cout << endl;
    }

    file.close();
    return 0;
}