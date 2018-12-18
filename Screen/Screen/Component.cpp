#include "GameObject.h"
#include "Component.h"




void MoveScript::update() {
    if (InputManager::GetKeyDown(KeyCode::LeftArrow)) {
        cout << "move left" << endl;
        cout << (gameObject->getName()) << endl;
    }
    if (InputManager::GetKeyDown(KeyCode::RightArrow)) {
        cout << "move right" << endl;
    }
}

void MyNewScript::start()
{
    n_frames = 1000;
}

void MyNewScript::update()
{
    if (n_frames == 0) {
        cout << "time expired" << endl;
        n_frames = 1000;
        return;
    }
    --n_frames;
}

void AutoMoveScript::update() {
    if (InputManager::GetKeyDown(KeyCode::Space)) {
        cout << "FIRED" << endl << endl;
    }
}