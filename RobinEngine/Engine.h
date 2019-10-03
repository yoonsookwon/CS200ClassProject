#pragma once
#include  "WindowContainer.h"

class Engine : WindowContainer
{
public:
	bool CreateAndShowWindow(const wchar_t* title, int w, int h);
	bool ProcessMessage();
	Engine() = default;

	void Init();
	void Update();
	void Delete();

private:
	bool isRunning = false;
	float dt;
};