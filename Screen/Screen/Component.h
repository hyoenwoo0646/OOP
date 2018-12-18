#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>
#include "Vector2.h"
#include "InputManager.h"

class GameObject;
class Transform;

using namespace std;

class Component {
    
protected:
    friend class GameObject;
    GameObject* gameObject;
    Transform* transform;

    virtual void start() { cout << "comp start" << endl;  }
    virtual void update() {}
    virtual void onDestroy() {}
public:
    Component(GameObject* gameObject, Transform* transform) : gameObject(gameObject), transform(transform) {  }

    void Start() {
        start(); 
    }

    virtual ~Component() { onDestroy(); }

};

class Transform : public Component {
    Vector2 position;
    Vector2 rotation;
    Vector2 scale;
public:
    Transform(GameObject *gameObject,
        const Vector2& pos = Vector2::zero,
        const Vector2& rotation = Vector2::zero,
        const Vector2& scale = Vector2::one
        ) 
        : Component(gameObject, this),
        position(pos), rotation(rotation), scale(scale)
    {}

};

class MoveScript : public Component {

protected:
    void start() { cout << "move script start" << endl;  }
    void update();
    
public:
    MoveScript(GameObject *gameObject, Transform* transform) : Component(gameObject, transform) {}
};

class AutoMoveScript : public Component {

protected:
    void start() { cout << "auto move script start" << endl; }
    void update();
public:
    AutoMoveScript(GameObject *gameObject, Transform* transform) : Component(gameObject, transform) {}
};

class MyNewScript : public Component {
    int n_frames; 
protected:
    void start();
    void update();
public:
    MyNewScript(GameObject* gameObject, Transform* transform) :
        Component(gameObject, transform) {}
};
#endif /* _COMPONENT_H_ */
