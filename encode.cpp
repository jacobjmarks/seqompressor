#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>

using namespace std;

char encode(queue<char> * twomer) {
    char encoded = 0;
    for (int i = 1; i >= 0; i--) {
        switch ((*twomer).front()) {
            case 'A': encoded |= 0x8 << 4 * i; break;
            case 'C': encoded |= 0x4 << 4 * i; break;
            case 'G': encoded |= 0x2 << 4 * i; break;
            case 'T': encoded |= 0x1 << 4 * i; break;
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
            default: break;
        }
        (*twomer).pop();
    }

    return encoded;
}

int main(int argc, char* argv[]) {
    // ARGUMENT PARSING ---------------------------------------
    auto usage = [&argv](string message){
        if (message != "") cerr << message << endl;
        fprintf(stderr, "Usage: %s [-H] file\n", argv[0]);
        fprintf(stderr, "  -H : Retain sequence headers.\n");
        return 1;
    };

    if (argc < 2) return usage("");
    if (argc > 3) return usage("Too many arguments!");

    static bool retain_headers = false;
    static string filename;

    for (int i = 1; i < argc; i++) {
        auto arg = [&argv, i](string arg){
            return !strcmp(argv[i], arg.c_str());
        };

        if (arg("-H")) {
            retain_headers = true;
            continue;
        }
        
        filename = argv[i];
    }
    if (filename.empty()) return usage("Please specify file!");
    // --------------------------------------------------------

    ifstream file;
    file.open(filename);
    if (!file.is_open()) throw runtime_error("Cannot open file: " + filename);


    char ch;
    queue<char> twomer;
    while ((ch = file.get()) != EOF) {
        if (ch == '\r') {
            // Skip
        } else if (ch == '\n') {
            if (file.peek() == '>') {
                if (twomer.size() == 1) {
                    // Odd length sequence
                    twomer.push(0);
                    cout << encode(&twomer);
                }
                if (retain_headers) cout << endl;
            } 
        } else if (ch == '>') {
            if (retain_headers) {
                do {
                    cout << ch;
                } while((ch = file.get()) != '\n');
                cout << endl;
            } else {
                if ((int)file.tellg() != 1) cout << endl;
                file.ignore(UINT32_MAX, '\n');
            }
        } else {
            twomer.push(ch);
            if (twomer.size() == 2) {
                cout << encode(&twomer);
            }
        }
    }
    cout << endl;
    
    file.close();
    return 0;
}