#include "winruntimemodule.h"

namespace cepp {

WindowsRuntimeModule::WindowsRuntimeModule() : mWindowTitle("CeppEngine"), mWidth(800), mHeight(600), mWindowHandle(NULL)
{

}

void WindowsRuntimeModule::initialize()
{
    WNDCLASS wndclass = { 0 };
    DWORD    wStyle = 0;
    RECT     windowRect;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = (WNDPROC)WindowProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = L"opengles2.0";

    if (!RegisterClass(&wndclass))
        return; // fail!

    wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

    // Adjust the window rectangle so that the client area has
    // the correct number of pixels
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = mWidth - windowRect.left;
    windowRect.bottom = mHeight - windowRect.top;

    AdjustWindowRect(&windowRect, wStyle, FALSE);

    mWindowHandle = CreateWindow(
        L"opengles2.0",
        mWindowTitle.c_str(),
        wStyle,
        0,
        0,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        hInstance,
        NULL);

    // Set the ESContext* to the GWL_USERDATA so that it is available to the
    // ESWindowProc
    SetWindowLongPtr(mWindowHandle, GWL_USERDATA, (LONG)(LONG_PTR)this);

    if (mWindowHandle == NULL)
    {
        // TODO: Unregister window class if fail
        return; // fail!
    }

    ShowWindow(mWindowHandle, TRUE);
}

} // namespace cepp
