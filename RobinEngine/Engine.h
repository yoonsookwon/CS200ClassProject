#pragma once
#include  "WindowContainer.h"
#include "Timer.h"

class Engine : WindowContainer
{
public:
    bool Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
    void Update();
    void RenderFrame();
  
private:
    Timer timer;
    bool is_FullScreen = false;
    bool is_vSyncOn = false;
    int checVsync = 0;
};

