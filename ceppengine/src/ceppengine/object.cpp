#include "object.h"
#include <iostream>

namespace cepp {

Object::Object() : mRefCount(0)
{
}

Object::~Object()
{
    assert(mRefCount == 0);
}

} // namespace cepp
