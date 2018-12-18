#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class GameObject {
    string name;
    string tag;
    vector<Component *> components;
    vector<GameObject *> children;
    Transform* transform;

public:
    GameObject(const string& name, const string& tag="unknown") : name(name), tag(tag), transform(new Transform(this)) {
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
    void AddComponent() {
        T* t = new T(this, this->getTransform());
        if (!dynamic_cast<Component*>(t)) {
            delete t;
            return;
        }
        components.push_back(t);
    }

    template<typename T>
    Component* GetComponent() {
        for (auto comp : components)
        {
            if (dynamic_cast<T *>(comp) != nullptr) return comp;
        }
        return nullptr;
    }

    const string getName() {
        return name; 
    }

    

};
#endif