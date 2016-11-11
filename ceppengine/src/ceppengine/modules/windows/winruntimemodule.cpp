#include "winruntimemodule.h"
#include "../../engine.h"

namespace cepp {

WindowsRuntimeModule *WindowsRuntimeModule::sInstance = 0;

WindowsRuntimeModule *WindowsRuntimeModule::instance()
{
    return sInstance;
}

WindowsRuntimeModule::WindowsRuntimeModule() : mWindowTitle(L"CeppEngine"), mWidth(800), mHeight(600), mWindowHandle(NULL), proc(0)
{
    sInstance = this;
}

WindowsRuntimeModule::~WindowsRuntimeModule()
{
    if(mWindowHandle)
        CloseWindow(mWindowHandle);
}

HWND WindowsRuntimeModule::getWindowHandle() const
{
    return mWindowHandle;
}

std::wstring WindowsRuntimeModule::windowTitle() const
{
    return mWindowTitle;
}

void WindowsRuntimeModule::setWindowTitle(const std::wstring &title)
{
    mWindowTitle = title;
    if(mWindowHandle) {
        SetWindowText(mWindowHandle, mWindowTitle.c_str());
    }
}

Vector3 WindowsRuntimeModule::screenResolution() const
{
    return Vector3(mWidth, mHeight, 0);
}

void WindowsRuntimeModule::setScreenResolution(const Vector3 &res)
{
    mWidth = (int)res.x;
    mHeight = (int)res.y;
    if(mWindowHandle) {
        LPRECT rect;
        GetWindowRect(mWindowHandle, rect);
        HDWP info = BeginDeferWindowPos(1);
        info = DeferWindowPos(info, mWindowHandle, NULL, rect->left, rect->top, mWidth, mHeight, 0);
        EndDeferWindowPos(info);
    }
}

void WindowsRuntimeModule::initialize()
{
    WNDCLASS wndclass = { 0 };
    DWORD    wStyle = 0;
    RECT     windowRect;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = proc;
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

    if (mWindowHandle == NULL)
    {
        UnregisterClass(L"opengles2.0", hInstance);
        return; // fail!
    }

    ShowWindow(mWindowHandle, TRUE);
}

void WindowsRuntimeModule::preUpdate(float deltaTime)
{
    MSG msg = { 0 };
    int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
    if (gotMsg)
    {
        if (msg.message == WM_QUIT)
        {
            Engine::instance()->stop();
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else
    {
        SendMessage(mWindowHandle, WM_PAINT, 0, 0);
    }
}

} // namespace cepp
