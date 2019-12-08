
#pragma once
#include  "ErrorLogger.h"

class WindowContainer;

class RobinsWindow
{
public:
	bool Init(WindowContainer * pWindowContainer,HINSTANCE _hInstance, std::string _window_title, std::string _window_class, int _width, int _height);
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
