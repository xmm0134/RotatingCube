#pragma once
#include"D3DApp.h"


BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{ 
	D3DApp Window(hInstance, "Cube", 1920, 1080, false);

	while (true)
	{
		Window.Run();

		Window.PollWindowEvents();
		Sleep(1);
	}
}