/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#include "MouseClass.h"

void MouseClass::LeftPressed(int _x, int _y)
{
    this->leftIsDown = true;
    MouseEvent mouse_event(MouseEvent::EventType::Lpress, _x, _y);
    this->eventBuffer.push(mouse_event);
}

void MouseClass::LeftReleased(int _x, int _y)
{
    this->leftIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, _x, _y));
}

void MouseClass::RightPressed(int _x, int _y)
{
    this->rightIsDown = true;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Rpress,_x,_y));
}

void MouseClass::RightReleased(int _x, int _y)
{
    this->rightIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, _x, _y));
}

void MouseClass::MiddlePressed(int _x, int _y)
{
    this->mButtonIsDown = true;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Mpress, _x, _y));
}

void MouseClass::MiddleReleased(int _x, int _y)
{
    this->mButtonIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, _x, _y));
}

void MouseClass::WheelUp(int _x, int _y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, _x, _y));
}

void MouseClass::WheelDown(int _x, int _y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, _x, _y));
}

void MouseClass::WheelPressed(int _x, int _y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelPress , _x, _y));
}

void MouseClass::MouseMove(int _x, int _y)
{
    this->x = _x;
    this->y = _y;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, _x, _y));
}

void MouseClass::MouseMoveRaw(int _x, int _y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, _x, _y));
}

bool MouseClass::IsLeftDown()
{
    return this->leftIsDown;
}

bool MouseClass::IsMiddleDown()
{
    return this->mButtonIsDown;
}

bool MouseClass::IsRightDown()
{
    return this->rightIsDown;
}

int MouseClass::GetPosX()
{
    return this->x;
}

int MouseClass::GetPosY()
{
    return this->y;
}

MousePoint MouseClass::GetPos()
{
    return {this->x, this->y};
}

bool MouseClass::EventBufferisEmpty()
{
    return this->eventBuffer.empty();
}

MouseEvent MouseClass::ReadEvent()
{
    if (this->eventBuffer.empty()) 
    {
        return MouseEvent();
    }
    else {
        MouseEvent _event = this->eventBuffer.front();
        this->eventBuffer.pop();
        return _event;
    }
 
}
