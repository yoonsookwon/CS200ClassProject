

//struct PlatformImpl;
//enum Keyboard
//{
//	W, A, S, D,
//	None
//};
//
//enum MouseButtons
//{
//	Left,
//	Right
//};

//class RobinsWindow
//{
//public:
//	RobinsWindow();
//	~RobinsWindow();
//
//	bool CreateAndShowWindow(const wchar_t* title, int w, int h);
//
//	void PollEvents();
//	void CloseWindow();
//	bool ShouldQuit();
//
//	void SetOnKeyPressed(std::function<void(Keyboard)> callback);
//	void SetOnKeyReleased(std::function<void(Keyboard)> callback);
//private:
//	std::unique_ptr<PlatformImpl> pimpl{};
//};


#pragma once
#include  "ErrorLogger.h"

class WindowContainer;

class RobinsWindow
{
public:
	bool Init(WindowContainer * pWindowContainer,HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
    HWND GetHWND() const;
	~RobinsWindow();

private:
	void RegisterWindowClass();
	HWND handle = NULL;
	HINSTANCE hInstance = NULL;
    std::string window_title = "";
    std::wstring window_title_wide = L"";
    std::string window_class = "";
    std::wstring window_class_wide = L"";
    int width = 0;
    int height = 0;
};
