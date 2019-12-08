/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "MouseEvent.h"
#include <queue>

class MouseClass 
{
public:
    void LeftPressed(int _x, int _y);
    void LeftReleased(int _x, int _y);
    void RightPressed(int _x, int _y);
    void RightReleased(int _x, int _y);
    void MiddlePressed(int _x, int _y);
    void MiddleReleased(int _x, int _y);
    void WheelUp(int _x, int _y); 
    void WheelDown(int _x, int _y);
    void WheelPressed(int _x, int _y);
    void MouseMove(int _x, int _y);
    void MouseMoveRaw(int _x, int _y);

    bool IsLeftDown();
    bool IsMiddleDown();
    bool IsRightDown();

    int GetPosX();
    int GetPosY();
    MousePoint GetPos();
    bool EventBufferisEmpty();
    MouseEvent ReadEvent();

private:
    std::queue<MouseEvent> eventBuffer;
    bool leftIsDown = false;
    bool rightIsDown = false;
    bool mButtonIsDown = false;
    int x = 0;
    int y = 0;
};