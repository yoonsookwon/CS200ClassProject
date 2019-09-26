#include "RudysWindow.h"
#include "Win32OS.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	RudysWindow window;
	window.CreateAndShowWindow(L"Hello", 800, 600);
	while(!window.ShouldQuit())
	{
		window.PollEvents();
		// update logic
		// draw stuff
	}
	
	return 0;
}

