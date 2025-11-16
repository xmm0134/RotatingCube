#include"D3DApp.h"


BOOL WINAPI WinMain(HINSTANCE hinstance, HINSTANCE pinstance, LPSTR lpcmdline, int showcmd)
{
	D3DApp Client(hinstance, "D3D11", 1920, 1080, FALSE);

	while (true)
	{
		Client.Run();
		Client.PollWindowEvents();
	}
}