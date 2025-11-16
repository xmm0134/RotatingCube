#pragma once

#include<windows.h>

 extern void Init();
 extern void OnKeyPress(WPARAM wparam);
 extern void OnLeftMousePress(LPARAM lparam);
 extern void OnLeftMouseRelease();
 extern void OnRightMousePress();
 extern void OnRightMouseRelease();
 extern void OnMouseMove(WPARAM wparam, LPARAM lparam);
 extern void OnMouseWheel(WPARAM wpara, LPARAM lpara);
 extern void OnKeyRelease(WPARAM wparam, LPARAM lparam);
 extern bool IsKeyPressed(unsigned char Vk);

 __declspec(selectany)bool ScrollWheel = false;
 __declspec(selectany)bool Isdragging;
 __declspec(selectany)float MouseWheelData = 0;
 __declspec(selectany)float PrevMouseX;
 __declspec(selectany)float PrevMouseY;
__declspec(selectany)float MouseX;
__declspec(selectany)float MouseY;
__declspec(selectany)bool KeyStates[256];
__declspec(selectany)bool LMouseButton = false;
__declspec(selectany)bool RMouseButton = false;


