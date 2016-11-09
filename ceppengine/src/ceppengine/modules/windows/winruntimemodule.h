#pragma once

#include "../runtimemodule.h"
#include <Windows.h>

namespace cepp {

class WindowsRuntimeModule : public RuntimeModule
{
    public:
        static WindowsRuntimeModule *instance();

        WindowsRuntimeModule();
        ~WindowsRuntimeModule();

        HWND getWindowHandle() const;

        virtual std::wstring windowTitle() const;
        virtual void setWindowTitle(const std::wstring &title);

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

