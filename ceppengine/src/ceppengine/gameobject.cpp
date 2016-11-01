#include "gameobject.h"

namespace cepp {

GameObject::GameObject() : mName("GameObject")
{

}

GameObject::GameObject(std::string name) : mName(name)
{

}

std::string GameObject::name() const
{
    return mName;
}

void GameObject::setName(std::string name)
{
    mName = name;
}

} // namespace cepp
