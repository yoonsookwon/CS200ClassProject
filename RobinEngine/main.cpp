#include "Engine.h"
#include "ErrorLogger.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
    Engine engine;
    engine.Init(hInstance, "RobinEngine", "MyWindowClass", 800, 600);

    while (engine.ProcessMessages() == true)
    {
        engine.Update();
    }
    return 0;
}


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


