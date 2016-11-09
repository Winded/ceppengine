#include "windowsinputmodule.h"

namespace cepp {

WindowsInputModule::WindowsInputModule() : mMouseScrollDelta(0)
{
    mLastMousePos.x = 0;
    mLastMousePos.y = 0;

    for(int i = 0; i < 255; i++) {
        mKeysPressed[i] = false;
        mKeysDown[i] = false;
        mKeysReleased[i] = false;
    }
    for(int i = 0; i < 3; i++) {
        mMButtonsPressed[i] = false;
        mMButtonsDown[i] = false;
        mMButtonsReleased[i] = false;
    }
}

Vector3 WindowsInputModule::mousePosition() const
{
    return mMousePos;
}

float WindowsInputModule::mouseScrollDelta() const
{
    return mMouseScrollDelta;
}

bool WindowsInputModule::isKeyPressed(int key) const
{
    return mKeysPressed[key];
}

bool WindowsInputModule::isKeyDown(int key) const
{
    return mKeysDown[key];
}

bool WindowsInputModule::isKeyReleased(int key) const
{
    return mKeysReleased[key];
}

bool WindowsInputModule::isMouseButtonPressed(int key) const
{
    return mMButtonsPressed[key];
}

bool WindowsInputModule::isMouseButtonDown(int key) const
{
    return mMButtonsDown[key];
}

bool WindowsInputModule::isMouseButtonReleased(int key) const
{
    return mMButtonsReleased[key];
}

void WindowsInputModule::updateMousePosition(const POINT &newPoint)
{
    mMousePos = Vector3((float)newPoint.x, (float)newPoint.y, 0);
}

void WindowsInputModule::updateMouseDelta(float delta)
{
    mMouseScrollDelta = delta;
}

void WindowsInputModule::setKeyDown(int key)
{
    mKeysPressed[key] = true;
    mKeysDown[key] = true;
}

void WindowsInputModule::setKeyUp(int key)
{
    mKeysReleased[key] = true;
    mKeysDown[key] = false;
}

void WindowsInputModule::setMouseButtonDown(int button)
{
    mMButtonsPressed[button] = true;
    mMButtonsDown[button] = true;
}

void WindowsInputModule::setMouseButtonUp(int button)
{
    mMButtonsReleased[button] = true;
    mMButtonsDown[button] = false;
}

void WindowsInputModule::postUpdate(float deltaTime)
{
    mMouseScrollDelta = 0;
    for(int i = 0; i < 255; i++) {
        mKeysPressed[i] = false;
        mKeysReleased[i] = false;
    }
    for(int i = 0; i < 3; i++) {
        mMButtonsPressed[i] = false;
        mMButtonsReleased[i] = false;
    }
}

} // namespace cepp
