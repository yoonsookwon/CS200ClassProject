#pragma once
struct  MousePoint
{
    int x;
    int y;
};

class MouseEvent {
public:
    enum EventType
    { 
        Lpress,
        LRelease,
        Rpress,
        RRelease,
        Mpress,
        MRelease,
        WheelUp,
        WheelDown,
        WheelPress,
        Move,
        RAW_MOVE,
        Invalid
    };
private:
    EventType type;
    int x;
    int y;
public:
    MouseEvent();
    MouseEvent(const EventType type, const int x, const int y);
    bool isValid() const;
    EventType GetType() const;
    MousePoint GetPos() const;
    int GetPosX() const;
    int GetPosY() const;
};