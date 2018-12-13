#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>

class GameObject;

using namespace std;

class Component {
    GameObject* gameObject;
    Transform* transform;
    friend class GameObject;
protected:
    virtual void start() {}
    virtual void update() {}
    virtual void onDestroy() {}
public:
    Component(GameObject* gameObject, Transform* transform) : gameObject(gameObject), transform(transform) { start(); }

    virtual ~Component() { onDestroy(); }

};

class Transform : public Component {
    Vector2 position;
    Vector2 rotation;
    Vector2 scale;
public:
    Transform(GameObject *gameObject) : Component(gameObject, this) {}

};

class MoveScript : public Component {

protected:
    void start() { cout << "hehe" << endl;  }
public:
    MoveScript(GameObject *gameObject, Transform* transform) : Component(gameObject, transform) {}
};

class AutoMoveScript : public Component {

protected:
    void start() { cout << "auto hehe" << endl; }
public:
    AutoMoveScript(GameObject *gameObject, Transform* transform) : Component(gameObject, transform) {}
};
#endif /* _COMPONENT_H_ */
