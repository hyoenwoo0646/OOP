#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
#include "InputManager.h"
#include "GameObject.h"

using namespace std;


class Scene {

    vector<GameObject *> gameObjects;
    bool exitFlag;

public:
    Scene(): exitFlag(false) {
        auto player = new GameObject;
        //player->AddComponent<MoveScript>();
        auto enemy = new GameObject;
        //enemy->AddComponent<AutoMoveScript>();

        gameObjects.push_back(player);
        gameObjects.push_back(enemy);        
    }
    ~Scene() {
        while (!gameObjects.empty()) {
            auto object = gameObjects.back();
            delete object;
            gameObjects.pop_back();
        }
    }

    void loop()
    {
        while (exitFlag == false) {
            // handle input
            if (InputManager::GetKeyDown(KeyCode::Escape)) break;

            for (auto obj : gameObjects)
            {
                //obj->update();
            }

            InputManager::endOfFrame();
        }
    }

};

#endif /* _SCENE_H_ */
