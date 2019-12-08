/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#include "WindowContainer.h"
#include  "resource1.h"

bool RobinsWindow::Init(WindowContainer * pWindowContainer,HINSTANCE _hInstance, std::string _window_title, std::string _window_class, int _width, int _height)
{
    this->hInstance = _hInstance;
    this->width = _width;
    this->height = _height;
    this->window_title = _window_title;
    this->window_title_wide = StringConverter::StringToWide(this->window_title);
    this->window_class = _window_class;
    this->window_class_wide = StringConverter::StringToWide(this->window_class);

    this->RegisterWindowClass();

    int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
    int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

    RECT wr; //Window Rectangle
    wr.left = centerScreenX;
    wr.top = centerScreenY;
    wr.right = wr.left + this->width;
    wr.bottom = wr.top + this->height;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    this->handle = CreateWindowEx(0,
        this->window_class_wide.c_str(),
        this->window_title_wide.c_str(),
        WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX|WS_SYSMENU,
        wr.left, // Window X Position
        wr.top,  // Window Y Position
    wr.right - wr.left,
   wr.bottom - wr.top,
        NULL,
        NULL,
        this->hInstance,
        pWindowContainer);


    if (this->handle == NULL) {
        ErrorLogger::Log(GetLastError(), "CreateWindow Failed for" + this->window_title);
        return false;
    }

    ShowWindow(this->handle, SW_SHOW);
    SetForegroundWindow(this->handle);
    SetFocus(this->handle);

    return true;
}

bool RobinsWindow::ProcessMessages()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (PeekMessage(&msg,
        this->handle,
        0,
        0, PM_REMOVE)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //Check if the window was closed
    if (msg.message == WM_NULL) {

        if (!IsWindow(this->handle)) {
            this->handle = NULL;
            UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
            return false;
        }
    }
    //Always return true if window still exist
    return true;
}


HWND RobinsWindow::GetHWND() const
{
    return  this->handle;
}

RobinsWindow::~RobinsWindow() {
    if (this->handle != NULL) {
        UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
        DestroyWindow(handle);
    }
}
LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    default :
    {
        WindowContainer * const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        
        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
}
LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        WindowContainer * pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
        if (pWindow == nullptr) {
            ErrorLogger::Log("Critical Error: Pointer to window container is null  during WM_NCCREATE.");
            exit(-1);
        }
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
     }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

}

void RobinsWindow::RegisterWindowClass()
{
    WNDCLASSEX wc;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = HandleMessageSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = this->hInstance;
    wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));
    wc.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = this->window_class_wide.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);
}
