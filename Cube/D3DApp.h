#pragma once
#include<iostream>
#include<optional>
#include<windows.h>
#include"Renderer.h"
#include"Time.h"
#include"InputHandler.h"

class D3DApp
{
protected:
	std::optional<Renderer> Graphics;
	int Width;
	int Height;
	HWND hwnd;
	HINSTANCE hinst;
	MSG msg;
	RECT wr;
	double FrameTime;
	double SecondsPerCount;
	int FrameCount;

public: 
	float FPS = NULL;

public:
	D3DApp(HINSTANCE hinstance, const char* WindowName, int width, int height, bool Windowed);
	HWND GetHWND();
	void PollWindowEvents();
	void Run();

private:
	void Registorclass();
	void CalculateElapsedFrames();
};