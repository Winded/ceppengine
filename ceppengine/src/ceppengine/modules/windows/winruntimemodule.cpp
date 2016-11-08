#include "winruntimemodule.h"
#include "../../engine.h"

namespace cepp {

LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT  lRet = 1;

    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
        WindowsRuntimeModule *esContext = (WindowsRuntimeModule*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        // draw?

        ValidateRect(esContext->getWindowHandle(), NULL);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CHAR:
    {
        POINT      point;
        WindowsRuntimeModule *esContext = (WindowsRuntimeModule*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        GetCursorPos(&point);

        // input handling?
    }
    break;

    default:
        lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    }

    return lRet;
}

WindowsRuntimeModule::WindowsRuntimeModule() : mWindowTitle(L"CeppEngine"), mWidth(800), mHeight(600), mWindowHandle(NULL)
{
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

    // Add pointer to module into window so we can access it with WindowProc
    SetWindowLongPtr(mWindowHandle, GWLP_USERDATA, (LONG_PTR)(void*)this);

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
