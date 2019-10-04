#include "MouseClass.h"

void MouseClass::LeftPressed(int x, int y)
{
    this->leftIsDown = true;
    MouseEvent mouse_event(MouseEvent::EventType::Lpress, x, y);
    this->eventBuffer.push(mouse_event);
}

void MouseClass::LeftReleased(int x, int y)
{
    this->leftIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
}

void MouseClass::RightPressed(int x, int y)
{
    this->rightIsDown = true;
    //MouseEvent mouse_event(MouseEvent::EventType::LRelease, x, y);
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Rpress,x,y));
}

void MouseClass::RightReleased(int x, int y)
{
    this->rightIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void MouseClass::MiddlePressed(int x, int y)
{
    this->mButtonIsDown = true;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Mpress, x, y));
}

void MouseClass::MiddleReleased(int x, int y)
{
    this->mButtonIsDown = false;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void MouseClass::WheelUp(int x, int y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void MouseClass::WheelDown(int x, int y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void MouseClass::WheelPressed(int x, int y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelPress , x, y));
}

void MouseClass::MouseMove(int x, int y)
{
    this->x = x;
    this->y = y;
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

void MouseClass::MouseMoveRaw(int x, int y)
{
    this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
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
