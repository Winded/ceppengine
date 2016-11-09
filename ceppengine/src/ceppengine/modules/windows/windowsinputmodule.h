#pragma once

#include "../inputmodule.h"
#include <Windows.h>

namespace cepp {

/**
 * Input module for Windows platform. This mostly adds update methods that should be implemented into the WNDPROC method.
 */
class WindowsInputModule : public InputModule
{
    public:
        WindowsInputModule();

        virtual Vector3 mousePosition() const;

        virtual float mouseScrollDelta() const;

        virtual bool isKeyPressed(int key) const;
        virtual bool isKeyDown(int key) const;
        virtual bool isKeyReleased(int key) const;

        virtual bool isMouseButtonPressed(int key) const;
        virtual bool isMouseButtonDown(int key) const;
        virtual bool isMouseButtonReleased(int key) const;

        // Update methods for WNDPROC processor

        void updateMousePosition(const POINT &newPoint);
        void updateMouseDelta(float delta);

        void setKeyDown(int key);
        void setKeyUp(int key);

        void setMouseButtonDown(int button);
        void setMouseButtonUp(int button);

        virtual void postUpdate(float deltaTime);

    private:
        POINT mLastMousePos;

        Vector3 mMousePos;
        float mMouseScrollDelta;

        bool mKeysPressed[255];
        bool mKeysDown[255];
        bool mKeysReleased[255];

        bool mMButtonsPressed[3];
        bool mMButtonsDown[3];
        bool mMButtonsReleased[3];
};

} // namespace cepp
