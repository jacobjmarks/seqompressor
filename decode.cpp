#include <iostream>
#include <fstream>

using namespace std;

void decode(char * decoded, char encoded) {
    for (uint i = 0; i < 2; i++) {
        switch (encoded >> (4 * i) & 0b00001111) {
            case 0x8: decoded[i] = 'A'; break;
            case 0x4: decoded[i] = 'C'; break;
            case 0x2: decoded[i] = 'G'; break;
            case 0x1: decoded[i] = 'T'; break;
            case 0x0: decoded[i] = 'U'; break;
            case 0x9: decoded[i] = 'W'; break;
            case 0x6: decoded[i] = 'S'; break;
            case 0xC: decoded[i] = 'M'; break;
            case 0x3: decoded[i] = 'K'; break;
            case 0xA: decoded[i] = 'R'; break;
            case 0x5: decoded[i] = 'Y'; break;
            case 0x7: decoded[i] = 'B'; break;
            case 0xB: decoded[i] = 'D'; break;
            case 0xD: decoded[i] = 'H'; break;
            case 0xE: decoded[i] = 'V'; break;
            case 0xF: decoded[i] = 'N'; break;
            default: throw runtime_error("Unhandled encoding.");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) throw invalid_argument("Please specify file to decode.");
    ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) throw runtime_error("Cannot open file.");

    char ch;
    char twomer[2];
    while ((ch = file.get()) != EOF) {
        if (ch == '\n') {
            cout << endl;
        } else {
            decode(twomer, ch);
            cout << twomer[0] << twomer[1];
        }
    }

    file.close();
    return 0;
}