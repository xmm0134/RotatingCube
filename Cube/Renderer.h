#pragma once
#include<optional>
#include<windows.h>
#include<d3d11.h>
#include"Cube.h"
#include"UI.h"

class Renderer 
{
private:
	HWND hwnd;
	ID3D11Device* Device;
	ID3D11DeviceContext* Devcon;
	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* RenderTarget;
	ID3D11InputLayout* InputLayout;
	ID3D11RasterizerState* RasterState;
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11DepthStencilState* DepthStencilState;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11Buffer* ConstantBuffer;
	ID3D11Texture2D* DepthStencilBuffer;

	float Aspect_Ratio;
	Cube cube;
	std::optional<UI> UserInterface;
	Matrix4x4 VP;

	float bg[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	bool InitShaders();
	bool InitObjects();
	void BeginFrame();
	void Endframe();

public:
	Renderer(HWND hwnd, float Width, float Height, bool Windowed);
	~Renderer();
	void UpdateModles();
	void Render();
};
