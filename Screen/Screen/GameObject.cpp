#include "GameObject.h"
#include "Component.h"

void GameObject::update()
{
    for (auto comp : components)
        comp->update();
}

template<typename T>
void GameObject::AddComponent<T>()
{
    T* t = new T(this, this->getTransform());
    if (!dynamic_cast<Component*>(t)) {
        delete t;
        return;
    }
    components.push_back(t);
}