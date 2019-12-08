/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include  "RobinsWindow.h"
#include  "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"
#include  "Graphics\Graphics.h"

class WindowContainer
{
public:
    WindowContainer();
    LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	RobinsWindow robins_windows;
    keyboardClass keyboard;
    MouseClass mouse;
    Graphics gfx;
    Model model;
private:
};
