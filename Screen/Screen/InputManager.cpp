#include <iostream>
#include "InputManager.h"
using namespace std;

int InputManager::major = -1;
int InputManager::minor = 0;
bool InputManager::prefetch = false;
map<KeyCode, pair<int, int>> InputManager::keyCodeTable = {
    { KeyCode::None,{ -1, 0 } },
    { KeyCode::Escape,{ 27, 0 } },
    { KeyCode::Space,{ ' ', 0 } },
    { KeyCode::LeftArrow,{ 224, 75 } },
    { KeyCode::RightArrow,{ 224, 77 } },
    { KeyCode::UpArrow,{ 224, 72 } },
    { KeyCode::DownArrow,{ 224, 80 } }
};
