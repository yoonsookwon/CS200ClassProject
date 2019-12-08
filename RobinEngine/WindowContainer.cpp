/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#include "WindowContainer.h"
#include <memory>

WindowContainer::WindowContainer()
{
    static bool raw_input_initialized = false;
    if (raw_input_initialized == false) 
    {
        RAWINPUTDEVICE rid;

        rid.usUsagePage = 0x01;  //Mouse
        rid.usUsage = 0x02;  
        rid.dwFlags = 0;
        rid.hwndTarget = NULL;

        if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE) {
            ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
            exit(-1);
        }
        raw_input_initialized = true;
    }
}

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        //Keyboard message
    case WM_KEYDOWN: {
        unsigned char keycode = static_cast<unsigned char>(wParam);
        if (keyboard.IsKeysAutoRepeat()) {
            keyboard.OnKeyPressed(keycode);
        }
        else 
        {
            const bool wasPressed = lParam & 0x40000000;
            if (!wasPressed) {
                keyboard.OnKeyPressed(keycode);
            }
        }
        return 0;
    }
    case WM_KEYUP: {
        unsigned char keycode = static_cast<unsigned char>(wParam);
        keyboard.OnKeyReleased(keycode);
        return 0;
     }

    case WM_CHAR: {
        unsigned char ch = static_cast<unsigned char>(wParam);
        if (keyboard.IsCharsAutoRepeat()) 
        {
            keyboard.OnChar(ch);
        }
        else
        {
            //If the value is 0 that meaning key being press;
            const bool wasPressed = lParam & 0x40000000;
            if (!wasPressed) {
                keyboard.OnChar(ch);
            }
        }
        return 0;
    }
     //Mouse message
    case WM_MOUSEMOVE: 
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.MouseMove(x, y);
        return 0;
    }
    case WM_LBUTTONDOWN: 
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.LeftPressed(x, y);
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.RightPressed(x, y);
        return 0;
    }
    case WM_LBUTTONUP:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.LeftReleased(x, y);
        return 0;
    }
    case WM_RBUTTONUP:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.RightReleased(x, y);
        return 0;
    }
    case WM_MBUTTONDOWN: 
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.MiddlePressed(x, y);
        return 0;
    }
    case WM_MBUTTONUP:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouse.MiddleReleased(x, y);
        return 0;
    }
    case WM_MOUSEWHEEL: 
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        //It's working for wheel up
        if(GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        {
            mouse.WheelUp(x, y);
        }
        else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) 
        {
            mouse.WheelDown(x, y);
        }
        break;
    }
    case WM_INPUT: 
    {
        UINT dataSize = 0;

        GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
        if (dataSize > 0) {
            std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize,sizeof(RAWINPUTHEADER)== dataSize))
            {
                RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
                if (raw->header.dwType == RIM_TYPEMOUSE) {
                    mouse.MouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
                }
            }
        }
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
