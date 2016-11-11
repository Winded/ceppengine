#pragma once

#include "../runtimemodule.h"
#include <Windows.h>
#include <EGL/eglplatform.h>

namespace cepp {

/**
 * Runtime module for the Windows platform. This uses the Windows API to create a window.
 */
class WindowsRuntimeModule : public RuntimeModule
{
    public:
        static WindowsRuntimeModule *instance();

        WindowsRuntimeModule();
        ~WindowsRuntimeModule();

        HWND getWindowHandle() const;

        virtual std::wstring windowTitle() const;
        virtual void setWindowTitle(const std::wstring &title);

        virtual Vector3 screenResolution() const;
        virtual void setScreenResolution(const Vector3 &res);

        virtual void initialize();
        virtual void preUpdate(float deltaTime);

        WNDPROC proc;

    private:
        static WindowsRuntimeModule *sInstance;

        std::wstring mWindowTitle;
        int mWidth, mHeight;

        HWND mWindowHandle;
};

} // namespace cepp

