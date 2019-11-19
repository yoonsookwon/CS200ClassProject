#include "WindowContainer.h"
#include  "resource1.h"
//#include <winuser.h>

//#include "Win32OS.h"

//struct PlatformImpl
//{
//	std::function<void(Keyboard)> onKeyPressed;
//	std::function<void(Keyboard)> onKeyReleased;
//
//	POINT mousePosition{};
//	HWND windowHandle{};
//	WINDOWPLACEMENT windowPlacement = { sizeof(WINDOWPLACEMENT) };
//	bool shouldQuit = false;
//	HINSTANCE instanceHandle{};
//	bool CreateAndShowWindow(const wchar_t* title, int w, int h);
//	void PollEvents();
//	void CloseWindow();
//};
//
//namespace
//{
//	const wchar_t* WindowClassName = L"RobinWindowsWin324Fun";
//	LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
//		WPARAM wparam, LPARAM lparam);
//	bool RegisterWindowClass(HINSTANCE hinstance, LPCWSTR str, int iconid);
//
//}
//
//bool PlatformImpl::CreateAndShowWindow(const wchar_t* title, int w, int h)
//{
//	instanceHandle = GetModuleHandleW(nullptr);
//	if (const bool registered_wndclass =
//		RegisterWindowClass(instanceHandle, WindowClassName, 101);
//		!registered_wndclass)
//	{
//		MessageBox(nullptr, L"failed to register window class",
//			L"Error!", MB_ICONERROR);
//	}
//	const DWORD window_style = WS_OVERLAPPEDWINDOW;
//	int x = 0, y = 0;
//	const DWORD default_extra_style = 0L;
//	const HWND no_parent_window = nullptr;
//	const HMENU no_menus = nullptr;
//	const LPVOID nothing_for_wm_create = nullptr;
//
//	windowHandle =
//		CreateWindowEx(default_extra_style, WindowClassName,
//			title, window_style, x, y, w, h, no_parent_window, no_menus,
//			instanceHandle, nothing_for_wm_create);
//
//	if(windowHandle == nullptr)
//	{
//		ErrorLogger::Log(GetLastError(), "CreateWindowEx Failed!");
//		return false;
//	}
//	SetWindowLongPtr(windowHandle, GWLP_USERDATA,
//		reinterpret_cast<LONG_PTR>(this));
//
//	ShowWindow(windowHandle, SW_SHOWDEFAULT);
//	SetForegroundWindow(windowHandle);
//	UpdateWindow(windowHandle);
//
//	return false;
//}
//
//void PlatformImpl::PollEvents()
//{
//	// update mouse position
//	MSG msg{};
//	while (PeekMessage(&msg, nullptr,
//		0,
//		0, PM_REMOVE) != FALSE)
//	{
//		if (msg.message == WM_QUIT)
//		{
//			shouldQuit = true;
//		}
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//}
//
//void PlatformImpl::CloseWindow()
//{
//	PostMessage(windowHandle, WM_CLOSE, 0, 0);
//	shouldQuit = true;
//}
//
//
//RobinsWindow::RobinsWindow() :pimpl(new PlatformImpl)
//{
//}
//
//RobinsWindow::~RobinsWindow()
//{
//}
//
//bool RobinsWindow::CreateAndShowWindow(const wchar_t* title, int w, int h)
//{
//	pimpl->CreateAndShowWindow(title, w, h);
//	return true;
//}
//
//void RobinsWindow::PollEvents()
//{
//	pimpl->PollEvents();
//}
//
//void RobinsWindow::CloseWindow()
//{
//	pimpl->CloseWindow();
//}
//
//bool RobinsWindow::ShouldQuit()
//{
//	return pimpl->shouldQuit;
//}
//
//
//namespace
//{
//	bool RegisterWindowClass(HINSTANCE hinstance, LPCWSTR str, int iconid)
//	{
//		WNDCLASSEXW wcex;
//
//		wcex.cbSize = sizeof(WNDCLASSEX);
//
//		wcex.style = CS_OWNDC;
//		wcex.lpfnWndProc = WndProc;
//		wcex.cbClsExtra = 0;
//		wcex.cbWndExtra = 0;
//		wcex.hInstance = hinstance;
//		wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(iconid));
//		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//		wcex.lpszMenuName = nullptr;
//		wcex.lpszClassName = WindowClassName;
//		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iconid));
//
//		return RegisterClassExW(&wcex);
//	}
//
//	Keyboard ConvertWin32KeyToMyEnum(WPARAM key)
//	{
//		switch (key)
//		{
//		case 'W':return Keyboard::W;
//		case 'S':return Keyboard::S;
//		case 'A':return Keyboard::A;
//		case 'D':return Keyboard::D;
//		default: return Keyboard::None;
//		}
//	}
//
//	LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
//		WPARAM wparam, LPARAM lparam)
//	{
//		auto platformImpl =
//			reinterpret_cast<PlatformImpl*>(
//				GetWindowLongPtr(hwnd, GWLP_USERDATA));
//		switch (message)
//		{
//		case WM_SIZE:
//			// window resized
//			break;
//		case WM_SETFOCUS:
//			// window gains focus
//			break;
//		case WM_KILLFOCUS:
//			// loses focus
//			break;
//		case WM_CLOSE:
//			// maybe notify game that window is gone
//			DestroyWindow(hwnd);
//			break;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			break;
//		case WM_PAINT:
//		{
//			BeginPaint(hwnd, nullptr);
//			EndPaint(hwnd, nullptr);
//		}
//		break;
//
//		case WM_KEYDOWN:
//		{
//			auto key = wparam;
//
//			Keyboard button = ConvertWin32KeyToMyEnum(key);
//			if (platformImpl->onKeyPressed)
//				platformImpl->onKeyPressed(button);
//		}
//		break;
//		case WM_KEYUP:
//		{
//			auto key = wparam;
//			Keyboard button = ConvertWin32KeyToMyEnum(key);
//			platformImpl->onKeyReleased(button);
//		}
//		break;
//
//		case WM_MOUSEHWHEEL:
//		case WM_LBUTTONDOWN:
//		case WM_RBUTTONDOWN:
//			break;
//		default:
//			return DefWindowProc(hwnd, message, wparam, lparam);
//		}
//		return 0;
//
//	}
//
//}

bool RobinsWindow::Init(WindowContainer * pWindowContainer,HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
    this->hInstance = hInstance;
    this->width = width;
    this->height = height;
    this->window_title = window_title;
    this->window_title_wide = StringConverter::StringToWide(this->window_title);
    this->window_class = window_class;
    this->window_class_wide = StringConverter::StringToWide(this->window_class);

    this->RegisterWindowClass();

    int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
    int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

    RECT wr; //Window Rectangle
    //이거를 셋팅하면서 시작하는 윈도우 창을 설정가능?
    wr.left = centerScreenX;
    wr.top = centerScreenY;
    wr.right = wr.left + this->width;
    wr.bottom = wr.top + this->height;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    this->handle = CreateWindowEx(0,
        this->window_class_wide.c_str(),
        this->window_title_wide.c_str(),
        WS_CAPTION| WS_MINIMIZEBOX|WS_SYSMENU,
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

    /*case WM_CHAR:
    {
        unsigned char letter = static_cast<unsigned char>(wParam);
        return 0;
    }
    case WM_KEYDOWN:
    {
        unsigned char keycode = static_cast<unsigned char>(wParam);
        return 0;
    }*/
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
