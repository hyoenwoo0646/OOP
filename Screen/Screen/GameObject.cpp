#include "GameObject.h"
#include "Component.h"

void GameObject::update()
{
    for (auto comp : components)
        comp->update();
}
