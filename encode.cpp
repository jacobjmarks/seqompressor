#include <iostream>
#include <fstream>

using namespace std;

char encode(string twomer) {
    unsigned char encoded = 0;
    for (uint i = 0; i < 2; i++) {
        switch (twomer[i]) {
            case 'A': encoded |= 0x8 << 4 * i; break;
            case 'C': encoded |= 0x4 << 4 * i; break;
            case 'G': encoded |= 0x2 << 4 * i; break;
            case 'T': encoded |= 0x1 << 4 * i; break;
            case 'U': encoded |= 0x0 << 4 * i; break;
            case 'W': encoded |= 0x9 << 4 * i; break;
            case 'S': encoded |= 0x6 << 4 * i; break;
            case 'M': encoded |= 0xC << 4 * i; break;
            case 'K': encoded |= 0x3 << 4 * i; break;
            case 'R': encoded |= 0xA << 4 * i; break;
            case 'Y': encoded |= 0x5 << 4 * i; break;
            case 'B': encoded |= 0x7 << 4 * i; break;
            case 'D': encoded |= 0xB << 4 * i; break;
            case 'H': encoded |= 0xD << 4 * i; break;
            case 'V': encoded |= 0xE << 4 * i; break;
            case 'N': encoded |= 0xF << 4 * i; break;
            default: throw runtime_error((string)"Unhandled nucleotide: " + twomer[i]);
        }
    }

    return encoded;
}

int main(int argc, char* argv[]) {
    if (argc < 2) throw invalid_argument("Please specify file to encode.");
    ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) throw runtime_error("Cannot open file.");

    char ch;
    string twomer;
    while ((ch = file.get()) != EOF) {
        if (ch == '\n' || ch == '\r') {
            // Skip
        } else if (ch == '>') {
             if ((int)file.tellg() != 1) cout << endl;
             file.ignore(UINT32_MAX, '\n');
        } else {
            twomer.push_back(ch);

            if (twomer.length() == 2) {
                cout << encode(twomer);
                twomer.clear();
            }
        }
    }
    
    file.close();
    return 0;
}