#pragma once
#include "MouseEvent.h"
#include <queue>

class MouseClass 
{
public:
    void LeftPressed(int x, int y);
    void LeftReleased(int x, int y);
    void RightPressed(int x, int y);
    void RightReleased(int x, int y);
    void MiddlePressed(int x, int y);
    void MiddleReleased(int x, int y);
    void WheelUp(int x, int y); 
    void WheelDown(int x, int y);
    void WheelPressed(int x, int y);
    void MouseMove(int x, int y);
    void MouseMoveRaw(int x, int y);

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