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
    const float objectSpeed = 0.1f;
    while (!mouse.EventBufferisEmpty())
    {
        MouseEvent mouse_event = mouse.ReadEvent();

        if (mouse_event.GetType() == MouseEvent::EventType::RAW_MOVE) {
           // this->gfx.camera.AdjustRotation((float)mouse_event.GetPosY() * 0.01f, (float)mouse_event.GetPosX() * 0.01f, 0);
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelUp)
        {
           // this->gfx.camera.AdjustCameraZoom(0.01);
            this->gfx.camera.zoom += cameraSpeed;
            this->gfx.camera.UpdateViewMatrix();
            OutputDebugStringA("MouseWheelUp!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelDown && this->gfx.camera.zoom >0.1)
        {
          //  this->gfx.camera.AdjustCameraZoom( -0.01);
                
            this->gfx.camera.zoom -= cameraSpeed;
            this->gfx.camera.UpdateViewMatrix();
            OutputDebugStringA("MouseWheelDown!\n");
        }
   /*     if (mouse_event.GetType() == MouseEvent::EventType::WheelUp)
        {
            OutputDebugStringA("MouseWheelUp!\n");
        }*/
        if (mouse_event.GetType() == MouseEvent::EventType::Lpress)
        {
            OutputDebugStringA("MouseLeftPressed!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::Rpress)
        {
            OutputDebugStringA("MouseRightPressed!\n");
        }
    }

    if (keyboard.KeyIsPressed('W'))
    {
        this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
    }
    if (keyboard.KeyIsPressed('S'))
    {
        this->gfx.camera.AdjustPosition(0.0f, cameraSpeed , 0.0f);
        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
    }
    if (keyboard.KeyIsPressed('A'))
    {
        this->gfx.camera.AdjustPosition(cameraSpeed, 0.0f,0.0f);

    }
    if (keyboard.KeyIsPressed('D'))
    {
        this->gfx.camera.AdjustPosition(-cameraSpeed, 0.0f, 0.0f);
        //this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed );

    }
    if(keyboard.KeyIsPressed('N'))
    {
        if(this->gfx._state == LEVEL1)
        {
            this->gfx._state = LEVEL2;
        }
    }

    if (keyboard.KeyIsPressed('V'))
    {
        if (this->gfx.is_vSyncOn == false)
        {
            this->gfx.is_vSyncOn = true;
        }
        else
        {
            this->gfx.is_vSyncOn = false;
        }
    }


    if (keyboard.KeyIsPressed(VK_LEFT))
    {
      /*  this->gfx.Rectangle.translation.x -= objectSpeed;
        this->gfx.camera.UpdateViewMatrix();
       */
        this->gfx.Rectangle.AdjustPosition(-objectSpeed, 0.0f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_RIGHT))
    {
      //  this->gfx.Rectangle.translation.x += objectSpeed;
        //this->gfx.camera.UpdateViewMatrix();
        this->gfx.Rectangle.AdjustPosition(objectSpeed, 0.0f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_UP))
    {
       // this->gfx.Rectangle.translation.y += objectSpeed;
       // this->gfx.camera.UpdateViewMatrix();
        this->gfx.Rectangle.AdjustPosition(0.0f, objectSpeed, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_DOWN))
    {
       // this->gfx.Rectangle.translation.y -= objectSpeed;
      //  this->gfx.Rectangle.UpdateWorldMatrix();
     //   this->gfx.camera.UpdateViewMatrix();
        this->gfx.Rectangle.AdjustPosition(0.0f, -objectSpeed, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD1))
    {/*
        this->gfx.Rectangle.angle += objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
        this->gfx.Rectangle.AdjustRotation(objectSpeed);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD2))
    {
       /* this->gfx.Rectangle.angle -= objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
        this->gfx.Rectangle.AdjustRotation(-objectSpeed);
    }

    if (keyboard.KeyIsPressed(VK_NUMPAD3))
    {/*
        this->gfx.Rectangle.angle += objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
       this->gfx.Rectangle.AdjustScale(0.01f,0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD4))
    {/*
        this->gfx.Rectangle.angle += objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
        this->gfx.Rectangle.AdjustScale(-0.01f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD5))
    {/*
        this->gfx.Rectangle.angle += objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
        this->gfx.Rectangle.AdjustScale(0.0f, 0.01f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD6))
    {/*
        this->gfx.Rectangle.angle += objectSpeed;
        this->gfx.Rectangle.UpdateWorldMatrix();*/
        this->gfx.Rectangle.AdjustScale(0.0f, -0.01f);
    }


    if (keyboard.KeyIsPressed('F'))
    {
        this->gfx.FULLSCREEN(!is_FullScreen);
        is_FullScreen = !is_FullScreen;
    }

    if (keyboard.KeyIsPressed('Z'))
    {
      //  this->gfx.camera.angle -= cameraSpeed;
      //  this->gfx.camera.UpdateViewMatrix();
       this->gfx.camera.AdjustRotation(-cameraSpeed,0.0f,0.0f);
     //   this->gfx.camera.AdjustRotation(0.0f, 0.0f, -cameraSpeed);
    }
    if (keyboard.KeyIsPressed('X'))
    {
      //  this->gfx.camera.angle += cameraSpeed;
     //   this->gfx.camera.UpdateViewMatrix();
        this->gfx.camera.AdjustRotation(cameraSpeed, 0.0f, 0.0f);
      //  this->gfx.camera.AdjustRotation(0.0f, 0.0f, cameraSpeed);
    }
}

void Engine::RenderFrame()
{
    gfx.RenderFrame();
}
