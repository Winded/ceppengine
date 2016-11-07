#pragma once

#include "../runtimemodule.h"
#include <Windows.h>

namespace cepp {

class WindowsRuntimeModule : public RuntimeModule
{
    public:
        WindowsRuntimeModule();

        virtual void initialize();

    private:
        std::string mWindowTitle;
        int mWidth, mHeight;

        HWND mWindowHandle;
};

} // namespace cepp

