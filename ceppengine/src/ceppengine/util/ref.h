#pragma once

#include <vector>
#include <cassert>

namespace cepp {

/**
 * Smart pointer class that can delete objects from memory when no longer referenced by smart pointers.
 * NOTE: The pointed object type needs to implement addReference and removeReference for reference counting.
 */
template<class Type>
class Ref
{
    public:
        Ref();
        Ref(Type* value);
        Ref(Ref<Type> &other);
        ~Ref();

        Ref<Type> &operator =(const Ref<Type> &other);
        Ref<Type> &operator =(Type *pointer);
        Ref<Type> &operator =(int value);

        Type *operator ->();
        Type *operator ->() const;
        operator Type*();
        operator Type*() const;

    private:
        Type *mValue;
};

template<class Type>
Ref<Type>::Ref() : mValue(0)
{
}

template<class Type>
Ref<Type>::Ref(Type *value) : mValue(value)
{
    value->addReference();
}

template<class Type>
Ref<Type>::Ref(Ref<Type> &other) : mValue(other.mValue)
{
    other.mValue->addReference();
}

template<class Type>
Ref<Type>::~Ref()
{
    if(mValue != 0) {
        if(mValue->removeReference() == 0) {
            delete mValue;
        }
    }
}

template<class Type>
Ref<Type> &Ref<Type>::operator =(const Ref<Type> &other)
{
    if(mValue != 0) {
        if(mValue->removeReference() == 0) {
            delete mValue;
        }
    }
    std::cout << "shit" << std::endl;
    mValue = other.mValue;
    if(mValue != 0) {
        mValue->addReference();
    }
    return *this;
}

template<class Type>
Ref<Type> &Ref<Type>::operator =(Type *pointer)
{
    if(mValue != 0) {
        if(mValue->removeReference() == 0) {
            delete mValue;
        }
    }
    mValue = pointer;
    if(mValue != 0) {
        mValue->addReference();
    }
    return *this;
}

template<class Type>
Ref<Type> &Ref<Type>::operator =(int value)
{
    assert(value == 0);
    if(mValue != 0) {
        if(mValue->removeReference() == 0) {
            delete mValue;
        }
    }
    mValue = 0;
    return *this;
}

template<class Type>
Type *Ref<Type>::operator ->()
{
    assert(mValue != 0);
    return mValue;
}

template<class Type>
Type *Ref<Type>::operator ->() const
{
    assert(mValue != 0);
    return mValue;
}

template<class Type>
Ref<Type>::operator Type *()
{
    assert(mValue != 0);
    return mValue;
}

template<class Type>
Ref<Type>::operator Type *() const
{
    assert(mValue != 0);
    return mValue;
}

}

