#include  "Engine.h"

bool Engine::Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
    timer.Start();
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
    float dt = timer.GetMilisecondsElapsed();
    timer.Restart();

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

    //this->gfx.model.AdjustRotation(0.0f, 0.0f, 0.001f);
    const float cameraSpeed = 0.04f;
    while (!mouse.EventBufferisEmpty())
    {
        MouseEvent mouse_event = mouse.ReadEvent();

        if (mouse_event.GetType() == MouseEvent::EventType::RAW_MOVE) {
            this->gfx.camera.AdjustRotation((float)mouse_event.GetPosY() * 0.01f, (float)mouse_event.GetPosX() * 0.01f, 0);
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelUp)
        {
            this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
            OutputDebugStringA("MouseWheelUp!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelDown)
        {
            this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);

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

    if (keyboard.KeyIsPressed('W'))
    {
        XMVECTOR tmp = gfx.camera.GetRightVector();
      //  XMVectorGetX(tmp);
         float a = XMVectorGetX(tmp);
         float b = XMVectorGetY(tmp);
        //tmp.x * cameraspeed, tmp.y * cameraspeed
         this->gfx.camera.AdjustPosition( this->gfx.camera.GetForwardVector() * cameraSpeed * dt);
        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
    }
    if (keyboard.KeyIsPressed('S'))
    {
        this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed * dt);
        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
    }
    if (keyboard.KeyIsPressed('A'))
    {
        this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed * dt);

        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed);
    }

    if (keyboard.KeyIsPressed('D'))
    {
        this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed * dt);

    }
   // if(keyboard.KeyIsPressed('Q'))//LEFT
   // {
   ///*     this->gfx.model.rectPos1.x -= 0.01;
   //     this->gfx.model.rectPos2.x -= 0.01;
   //*/
   //     this->gfx.model.AdjustRectangleTranslation(-cameraSpeed,0.0f, -cameraSpeed,0.0f);
   // }
    if (keyboard.KeyIsPressed('77'))//RIGHT
    {
    }
    if (keyboard.KeyIsPressed('72'))//UP
    {
    }
    if (keyboard.KeyIsPressed('80'))//DOWN
    {
    }

    if (keyboard.KeyIsPressed('Z'))
    {
        this->gfx.camera.AdjustRotation(0.0f, 0.0f, -cameraSpeed);
    }
    if (keyboard.KeyIsPressed('X'))
    {
        this->gfx.camera.AdjustRotation(0.0f, 0.0f, cameraSpeed);
    }
}

void Engine::RenderFrame()
{
    gfx.RenderFrame();
}
