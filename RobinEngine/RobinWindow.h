#pragma once
#include  "ErrorLogger.h"

class RobinWindow
{
	public:
		bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
		bool ProcessMessages(); //return false = window close 
		~RobinWindow();
private:
	void RegisterWindowClass();
	HWND handle = nullptr; //Handle to this window
	HINSTANCE hInstance = nullptr;
	std::string window_title = "";
	std::wstring window_title_wide = L"";
	std::string window_class = "";
	std::string window_class_wide = L"";
	int width = 0;
	int height = 0;
	
};