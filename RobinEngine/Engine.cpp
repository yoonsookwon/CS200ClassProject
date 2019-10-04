#include  "Engine.h"

bool Engine::Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
   // keyboard.EnableAutoRepeatChars();
    return this->robins_windows.Init(this,hInstance,window_title,window_class,width,height);
    //In the future after initialize window we will do graphic
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
