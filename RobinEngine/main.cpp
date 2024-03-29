#include "Engine.h"
#include "ErrorLogger.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
    HRESULT hr = CoInitialize(NULL);
    if(FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to call Coinitialize.");
        return  -1;
    }
    Engine engine;
    if (engine.Init(hInstance, "RobinEngine", "MyWindowClass", 800, 600))
    {
        while (engine.ProcessMessages() == true)
        {
            engine.Update();
            engine.RenderFrame();
        }
    }
    return 0;
}
//The things that need to be implemented for drawing something
//INPUT ASSEMBLER - COMPLETED
//VERTEX SHADER - COMPLETED
//RASTERIZER - COMPLETED
//PIXEL SHADER- COMPLETED
//OUTPUT MERGER - COMPLETED


//create our vertex buffer
//Draw



//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hInstance);
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//	UNREFERENCED_PARAMETER(nCmdShow);
//
//	RobinsWindow window;
//	window.CreateAndShowWindow(L"RobinEngine", 800, 600);
//	while (!window.ShouldQuit())
//	{
//		window.PollEvents();
//		// update logic
//		// draw stuff
//	}
//
//	return 0;
//}


