#include "UI.h"

UI::UI(ID3D11Device* Device, ID3D11DeviceContext* Devcon, void* hwnd, int Width, int Height) : p_Device(Device), p_Devcon(Devcon), Width(Width), Height(Height),hwnd(hwnd)
{
	ImGui::CreateContext();
	ImGui_ImplDX11_Init(this->p_Device, this->p_Devcon);
	ImGui_ImplWin32_Init(this->hwnd);

	ImGui::StyleColorsLight();
	
}

void UI::Render_UI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(this->Width / 5, this->Height / 3.5));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Transformations", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::Checkbox("Rotations", &this->Rotate);
	if (Rotate)
	{
		ImGui::SliderFloat("Rotation Factor", &this->Rotate_Factor, 0.009f, 0.05f);
	}
	ImGui::Checkbox("Scaling", &this->Scale);
	if (Scale)
	{
		ImGui::SliderFloat("Scale Factor", &this->Scale_Factor, 0.01f, 0.05f);
	}

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UI::Clean_UI()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

ID3D11Device* UI::GetDevice()
{
	return this->p_Device;
}

ID3D11DeviceContext* UI::GetDeviceContext()
{
	return this->p_Devcon;
}
