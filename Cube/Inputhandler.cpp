#pragma once
#include "InputHandler.h"

inline void Init()
{
	for (short int i = 0; i < 256; i++)
	{
		KeyStates[i] = false;
	}
	return;
}

inline void OnKeyPress(WPARAM wparam)
{
	KeyStates[wparam] = true;
}

void OnLeftMousePress(LPARAM lparam)
{
	PrevMouseX = LOWORD(lparam);
	PrevMouseY = HIWORD(lparam);
	Isdragging = true;
	LMouseButton = true;
}

void OnLeftMouseRelease()
{
	Isdragging = false;
	LMouseButton = false;
}

void OnRightMousePress()
{
	RMouseButton = true;
}

void OnRightMouseRelease()
{
	RMouseButton = false;
}

void OnMouseMove(WPARAM wparam, LPARAM lparam)
{
	if (wparam == MK_LBUTTON)
	{
		LMouseButton = true;
	}

	MouseX = LOWORD(lparam);
	MouseY = HIWORD(lparam);
}

void OnMouseWheel(WPARAM wparam, LPARAM lparam)
{
	ScrollWheel = true;
	if (wparam == MK_LBUTTON)
	{
		LMouseButton = true;
	}
	MouseWheelData = GET_WHEEL_DELTA_WPARAM(wparam);
	MouseX = LOWORD(lparam);
	MouseY = HIWORD(lparam);
}

inline void OnKeyRelease(WPARAM wparam, LPARAM lparam)
{
	KeyStates[wparam] = false;
}

 inline bool IsKeyPressed(unsigned char Vk)
{
	if (KeyStates[Vk])
	{
		return true;
	}

	return false;
}

