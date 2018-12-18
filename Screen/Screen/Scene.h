#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"

using namespace std;


class Scene {

    vector<GameObject *> gameObjects;
    bool exitFlag;

public:
    Scene(): exitFlag(false) {
        auto player = new GameObject("player");
        player->AddComponent<MoveScript>();
        auto move = player->GetComponent<MoveScript>();
        move->Start();
        
        auto enemy = new GameObject("enemy");
        enemy->AddComponent<AutoMoveScript>();
        auto autoMove = enemy->GetComponent<AutoMoveScript>();
        autoMove->Start();
        enemy->AddComponent<MyNewScript>();
        auto myNew = enemy->GetComponent<MyNewScript>();
        myNew->Start();

        

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
                obj->update();
            }

            InputManager::endOfFrame();
        }
    }

};

#endif /* _SCENE_H_ */
