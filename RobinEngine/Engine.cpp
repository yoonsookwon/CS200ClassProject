#include  "Engine.h"
#include  "ScreenGrab.h"
#include "wincodec.h"
bool Engine::Init(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
    timer.Start();
    if (!this->robins_windows.Init(this, hInstance, window_title, window_class, width, height))
        return false;

    if (gfx.Init(this->robins_windows.GetHWND(), width, height))
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
        if (keycode == 27)
        {
        }
        if (kbe.IsPress()) {
            if(keycode == VK_NUMPAD9)
            {
                SaveWICTextureToFile(this->gfx.deviceContext.Get(),
                   this->gfx.backbuffer.Get(), GUID_ContainerFormatPng,L"SCREENSHOTaa.PNG");
            }

            if (keycode == 'V')
            {
                if (is_vSyncOn == false)
                {
                    this->gfx.is_vSyncOn = true;
                    is_vSyncOn = true;
                }
                else
                {
                    this->gfx.is_vSyncOn = false;
                    is_vSyncOn = false;
                }
            }
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
    const float cameraSpeed = 0.03f;
    const float objectSpeed = 1.f;
    while (!mouse.EventBufferisEmpty())
    {
        MouseEvent mouse_event = mouse.ReadEvent();

        if (mouse_event.GetType() == MouseEvent::EventType::WheelUp)
        {
            this->gfx.camera.zoom += cameraSpeed;
            this->gfx.camera.UpdateViewMatrix();
            OutputDebugStringA("MouseWheelUp!\n");
        }
        if (mouse_event.GetType() == MouseEvent::EventType::WheelDown && this->gfx.camera.zoom > 0.1)
        {

            this->gfx.camera.zoom -= cameraSpeed;
            this->gfx.camera.UpdateViewMatrix();
            OutputDebugStringA("MouseWheelDown!\n");
        }

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
    }
    if (keyboard.KeyIsPressed('S'))
    {
        this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
    }
    if (keyboard.KeyIsPressed('A'))
    {
        this->gfx.camera.AdjustPosition(cameraSpeed, 0.0f, 0.0f);

    }
    if (keyboard.KeyIsPressed('D'))
    {
        this->gfx.camera.AdjustPosition(-cameraSpeed, 0.0f, 0.0f);
    }

    if (keyboard.KeyIsPressed('N'))
    {
        if (this->gfx.current_state == LEVEL1)
        {
            this->gfx.current_state = LEVEL2;
        }
        checVsync++;
    }

    if (keyboard.KeyIsPressed(VK_LEFT))
    {
        this->gfx.Rectangle.AdjustPosition(-cameraSpeed, 0.0f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_RIGHT))
    {
        this->gfx.Rectangle.AdjustPosition(cameraSpeed, 0.0f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_UP))
    {
        this->gfx.Rectangle.AdjustPosition(0.0f, cameraSpeed, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_DOWN))
    {
        this->gfx.Rectangle.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD1))
    {
        this->gfx.Rectangle.AdjustRotation(cameraSpeed*2);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD2))
    {
        this->gfx.Rectangle.AdjustRotation(-cameraSpeed*2);
    }

    if (keyboard.KeyIsPressed(VK_NUMPAD3))
    {
        this->gfx.Rectangle.AdjustScale(0.01f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD4))
    {
        this->gfx.Rectangle.AdjustScale(-0.01f, 0.0f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD5))
    {
        this->gfx.Rectangle.AdjustScale(0.0f, 0.01f);
    }
    if (keyboard.KeyIsPressed(VK_NUMPAD6))
    {
        this->gfx.Rectangle.AdjustScale(0.0f, -0.01f);

    }
    if (this->gfx.current_state == LEVEL2 && keyboard.KeyIsPressed(VK_LEFT))
    {
        if (model.HierarchicalTYPE == Model::HierarchicalBODY)
        {
            this->gfx.ChulBody.AdjustPosition(-0.005f, 0.0f, 0.0f);
            this->gfx.ChulHead.AdjustRotation(objectSpeed);
            this->gfx.ChulHead.AdjustPosition(-0.005f, 0.0f, 0.0f);
            this->gfx.Chullegs.AdjustPosition(-0.005f, 0.0f, 0.0f);
            this->gfx.ChulLArm.AdjustPosition(-0.005f, 0.0f, 0.0f);
            this->gfx.ChulRArm.AdjustPosition(-0.005f, 0.0f, 0.0f);


            this->gfx.ChulRArm.AdjustScale(0.001f, 0.005f);
            this->gfx.ChulLArm.AdjustScale(0.001f, 0.005f);

        }
    }
    if (this->gfx.current_state == LEVEL2 && keyboard.KeyIsPressed(VK_RIGHT))
    {
        if (model.HierarchicalTYPE == Model::HierarchicalBODY)
        {
            this->gfx.ChulBody.AdjustPosition(0.005f, 0.0f, 0.0f);
            this->gfx.ChulHead.AdjustRotation(-objectSpeed);
            this->gfx.ChulHead.AdjustPosition(0.005f, 0.0f, 0.0f);
            this->gfx.Chullegs.AdjustPosition(0.005f, 0.0f, 0.0f);
            this->gfx.ChulLArm.AdjustPosition(0.005f, 0.0f, 0.0f);
            this->gfx.ChulRArm.AdjustPosition(0.005f, 0.0f, 0.0f);


            this->gfx.ChulRArm.AdjustScale(-0.001f, -0.005f);
            this->gfx.ChulLArm.AdjustScale(-0.001f, -0.005f);

        }
    }
    if (this->gfx.current_state == LEVEL2 && keyboard.KeyIsPressed(VK_UP))
    {
        if (model.HierarchicalTYPE == Model::HierarchicalBODY)
        {
            this->gfx.ChulBody.AdjustPosition(0.0f, 0.005f, 0.0f);
            this->gfx.ChulHead.AdjustRotation(-objectSpeed);
            this->gfx.ChulHead.AdjustPosition(0.0f, 0.005f, 0.0f);
            this->gfx.Chullegs.AdjustPosition(0.0f, 0.005f, 0.0f);
            this->gfx.ChulLArm.AdjustPosition(0.0f, 0.005f, 0.0f);
            this->gfx.ChulRArm.AdjustPosition(0.0f, 0.005f, 0.0f);


            this->gfx.Chullegs.AdjustScale(0.004f, 0.001f);
        }
    }
    if (this->gfx.current_state == LEVEL2 && keyboard.KeyIsPressed(VK_DOWN))
    {
        if (model.HierarchicalTYPE == Model::HierarchicalBODY)
        {
            this->gfx.ChulBody.AdjustPosition(0.0f, -0.005f, 0.0f);
            this->gfx.ChulHead.AdjustRotation(objectSpeed);
            this->gfx.ChulHead.AdjustPosition(0.0f, -0.005f, 0.0f);
            this->gfx.Chullegs.AdjustPosition(0.0f, -0.005f, 0.0f);
            this->gfx.ChulLArm.AdjustPosition(0.0f, -0.005f, 0.0f);
            this->gfx.ChulRArm.AdjustPosition(0.0f, -0.005f, 0.0f);

            this->gfx.Chullegs.AdjustScale(-0.004f, -0.001f);
        }
    }


    if (keyboard.KeyIsPressed('F'))
    {
        this->gfx.FULLSCREEN(!is_FullScreen);
        is_FullScreen = !is_FullScreen;
    }

    if (keyboard.KeyIsPressed('Z'))
    {
        this->gfx.camera.AdjustRotation(-cameraSpeed, 0.0f, 0.0f);
    }
    if (keyboard.KeyIsPressed('X'))
    {
        this->gfx.camera.AdjustRotation(cameraSpeed, 0.0f, 0.0f);
    }
}

void Engine::RenderFrame()
{

    gfx.RenderFrame();
}
