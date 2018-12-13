#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Component;
class Transform;

class GameObject {
    string name;
    string tag;
    vector<Component *> components;
    vector<GameObject *> children;
    Transform* transform;

public:
    GameObject(const string& name, const string& tag) : name(name), tag(tag), transform(new Transform) {
        components.push_back(transform);
    }
    ~GameObject() {
        while (!components.empty()){
            auto component = components.back();
            delete component;
            components.pop_back();
        }
        while (!children.empty())
        {
            auto child = children.back();
            delete child;
            children.pop_back();
        }
    }

    void update();

    Transform* getTransform() { return transform; }

    template<typename T>
    void AddComponent<T>();
    

};
#endif