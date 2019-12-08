/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include <chrono>

class Timer
{
public:
    Timer();
    double GetMilisecondsElapsed();
    void Restart();
    bool Stop();
    bool Start();
private:
    bool isrunning = false;
#ifdef _WIN32
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> stop;
#else
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> stop;
#endif
};