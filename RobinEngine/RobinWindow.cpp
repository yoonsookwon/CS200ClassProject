#include "RobinWindow.h"

bool RobinWindow::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0, this->window_class_wide.c_str(), this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
		, 0, 0, this->width, this->height, 
		NULL, NULL, this->hInstance, nullptr);
	
	return false;
}

void RobinWindow::RegisterWindowClass()
{
	//It's mentioned on tutorial 3
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}

