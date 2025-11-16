#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"

class UI
{
private:
	ID3D11Device* p_Device;
	ID3D11DeviceContext* p_Devcon;
	int Width;
	int Height;
	void* hwnd;
public:
	UI(ID3D11Device* Device, ID3D11DeviceContext* Devcon, void* hwnd, int Width, int height);
	void Render_UI();
	void Clean_UI();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

public:
	bool Rotate = true;
	bool Scale = true;

	float Scale_Factor = 0.01f;
	float Rotate_Factor = 0.01f;
};