#pragma once

#include <conio.h>
#include <map>
#include <algorithm>

using namespace std;

enum class KeyCode {
    None = 0,
    Backspace,
    Space,
    Escape,
    LeftArrow,
    RightArrow,
    UpArrow,
    DownArrow,
    A,
    D
};

class InputManager {
    static int major;
    static int minor;

    static bool prefetch;

    static map<KeyCode, pair<int, int>> keyCodeTable;

public:
    InputManager() {}

    static bool GetKeyDown(KeyCode key) {
        if (prefetch == false) {
            if (_kbhit()) {
                major = _getch();
                if (major == 0 || major == 224) {
                    minor = _getch();
                }
                cout << "major = " << major << ", minor = " << minor << endl;
            }
            
            prefetch = true;
        }
        auto res = keyCodeTable[key];
        return (res.first == major && res.second == minor);
    }

    static void endOfFrame() {
        prefetch = false;
        major = -1;
        minor = 0;
    }

};

