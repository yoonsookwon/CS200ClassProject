#include  "Engine.h"

bool Engine::Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
    if(!this->robins_windows.Init(this,hInstance,window_title,window_class,width,height))
        return false;

    //여기서 리턴 flase 인가 true인가?
    if(gfx.Init(this->robins_windows.GetHWND(), width, height))
        return true;

    return true;
    
}

bool Engine::ProcessMessages()
{
    return this->robins_windows.ProcessMessages();
}

void Engine::Update()
{
    while (!keyboard.CharBufferIsEmpty())
    {
        unsigned char ch = keyboard.ReadChar();
        std::string outmsg = "Char: ";
        outmsg += ch;
        outmsg += "\n";
        OutputDebugStringA(outmsg.c_str());
    }

    while (!keyboard.KeyBufferIsEmpty())
    {
        KeyboardEvent kbe = keyboard.ReadKey();
        unsigned char keycode = kbe.GetKeyCode();
        std::string outmsg = "";
        if(keycode == 27)
        {
        //    robins_windows.GetHWND()
         //   IsWindow(robins_windows.GetHWND()) = false;
          //  robins_windows.getMSG() = WM_NULL;
            //this->robins_windows.GetHWND() = NULL;
        }
        if (kbe.IsPress()) {
            outmsg += "key press: ";
        }
        if (kbe.IsRelease()) {
            outmsg += "key release: ";
        }
        outmsg += keycode;
        outmsg += "\n";
        OutputDebugStringA(outmsg.c_str());
    }
    while (!mouse.EventBufferisEmpty())
    {
        MouseEvent mouse_event = mouse.ReadEvent();
        if (mouse_event.GetType() == MouseEvent::EventType::WheelUp) 
        {
            OutputDebugStringA("MouseWheelUp!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelDown)
        {
            OutputDebugStringA("MouseWheelDown!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelUp)
        {
            OutputDebugStringA("MouseWheelUp!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::Lpress)
        {
            OutputDebugStringA("MouseLeftPressed!\n");
        }    
        if (mouse_event.GetType() == MouseEvent::EventType::Rpress)
        {
            OutputDebugStringA("MouseRightPressed!\n");
        }
     /*   if (mouse_event.GetType() == MouseEvent::EventType::RAW_MOVE)
        {   
        std::string outmsg = "X:  ";
        outmsg += std::to_string(mouse_event.GetPosX());
        outmsg += ", ";
        outmsg += "Y: ";
        outmsg += std::to_string(mouse_event.GetPosY());
        outmsg += "\n";
        OutputDebugStringA(outmsg.c_str());
        }*/
    }
}

void Engine::RenderFrame()
{
    gfx.RenderFrame();
}
