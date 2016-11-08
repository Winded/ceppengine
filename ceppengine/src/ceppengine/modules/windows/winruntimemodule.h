#pragma once

#include "../runtimemodule.h"
#include <Windows.h>

namespace cepp {

class WindowsRuntimeModule : public RuntimeModule
{
    public:
        WindowsRuntimeModule();
        ~WindowsRuntimeModule();

        HWND getWindowHandle() const;

        virtual std::wstring windowTitle() const;
        virtual void setWindowTitle(const std::wstring &title);

        virtual void initialize();
        virtual void preUpdate(float deltaTime);

    private:
        std::wstring mWindowTitle;
        int mWidth, mHeight;

        HWND mWindowHandle;
};

} // namespace cepp

