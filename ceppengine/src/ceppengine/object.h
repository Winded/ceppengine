#pragma once

#include <cassert>
#include <vector>

namespace cepp {

/**
 * Base class for all things CeppEngine.
 * The Object class implements reference counting, which enables the use of cepp::Ref smart pointers.
 */
class Object
{
    public:
        Object();
        ~Object();

        inline int addReference() {
            mRefCount++;
            return mRefCount;
        }

        inline int removeReference() {
            mRefCount--;
            assert(mRefCount >= 0);
            return mRefCount;
        }

    private:
        int mRefCount;
};

} // namespace cepp
