
#include "Renderer.h"
#include"Math.h"
#include"InputHandler.h"
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"Shaders_Byte_Code.h"

 float AngleX = 0;
 float AngleY = 0;
 float AngleZ = 0;
 float Scale = 0.0f;
 float Scaleinc = 0.0f;

float Clamp(float value, float value_min, float value_max) 
{
	if (value < value_min)
	{
		return value_min;
	}
	if (value > value_max)
	{
		return value_max;
	}

	return value;
}

void Renderer::UpdateModles()
{
	if (this->UserInterface->Rotate)
	{
		if (Isdragging)
		{
			AngleZ += (float)abs((int)(MouseX - PrevMouseX)) * this->UserInterface->Rotate_Factor;
			AngleY += (float)abs((int)(MouseY - PrevMouseY)) * this->UserInterface->Rotate_Factor;
		}
	}
	if (this->UserInterface->Scale)
	{
		if (MouseWheelData > 0 && ScrollWheel == true)
		{
			Scaleinc += this->UserInterface->Scale_Factor;
		}
		if (MouseWheelData < 0 && ScrollWheel == true)
		{
			Scaleinc -= this->UserInterface->Scale_Factor;
		}
	}
	Scale += Scaleinc;
	Scale = Clamp(Scale, 0.01f, 2.0f);
	cube.SetUpMMatrix(Vector4(0.0f, 0.0f, 0.0f, 1.0f), Scale, AngleX, AngleY, AngleZ); 
	Scale = 1.0f;
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	Devcon->Map(this->ConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MappedResource);
	Matrix4x4 MVP = this->VP * cube.GetModleMatrix(); 
	memcpy(MappedResource.pData, &MVP, sizeof(Matrix4x4));
	Devcon->Unmap(this->ConstantBuffer, NULL);
}

bool Renderer::InitShaders()
{
	D3D11_INPUT_ELEMENT_DESC Desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = Device->CreateInputLayout(Desc, 2, Vertex_Shader_ByteCode, sizeof(Vertex_Shader_ByteCode), &InputLayout);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Input Layout Failed!", "Error", MB_OKCANCEL);
		return false;
	}
	hr = Device->CreateVertexShader(Vertex_Shader_ByteCode, sizeof(Vertex_Shader_ByteCode), NULL, &VertexShader);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Vertex Shader Failed!", "Error", MB_OKCANCEL);
		return false;
	}

	hr = Device->CreatePixelShader(Pixel_Shader_Byte_Code, sizeof(Pixel_Shader_Byte_Code), NULL, &PixelShader);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Pixel Shader Failed!", "Error", MB_OKCANCEL);
		return false;
	}

	Devcon->VSSetShader(VertexShader, NULL, NULL);
	Devcon->PSSetShader(PixelShader, NULL, NULL);

	Devcon->IASetInputLayout(InputLayout);
}

bool Renderer::InitObjects()
{								
	Matrix4x4 Projection_Matrix = Math::ProjectionMatrix(this->Aspect_Ratio, 60.0f * (PI / 180.0f), 0.1f, 20.0f); // Aspect ratio, FOV, Znear, ZFar
	Vector3 CamPos(0.0f, 0.0f, 20.0f);
	Matrix4x4 View_Matrix = Math::ViewMatrix(CamPos, Vector3(0.0f, 0.0f, 0.0f));
	this->VP = Projection_Matrix * View_Matrix;
	
	D3D11_BUFFER_DESC Cbuffer;
	Cbuffer.ByteWidth = 4 * 16;
	Cbuffer.Usage = D3D11_USAGE_DYNAMIC;
	Cbuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Cbuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Cbuffer.MiscFlags = NULL;
	Cbuffer.StructureByteStride = NULL;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->VP;
	data.SysMemPitch = NULL;
	data.SysMemSlicePitch = NULL;

	Device->CreateBuffer(&Cbuffer, &data, &this->ConstantBuffer);
	Devcon->VSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	
	cube.SetUpMMatrix(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0);

	if (!cube.Init(this->Device, this->Devcon, this->SwapChain))
	{
		MessageBoxA(this->hwnd, "Cube Couldnt Be Initialized", "Error", MB_OKCANCEL);
		return false;
	}
}

Renderer::Renderer(HWND hwnd, float Width, float Height, bool Windowed)
{
	if (hwnd == nullptr)
	{
		return;
	}
	this->Aspect_Ratio = Width / Height;
	this->hwnd = hwnd;
	DXGI_SWAP_CHAIN_DESC SwapDesc;
	ZeroMemory(&SwapDesc, sizeof(SwapDesc));
	SwapDesc.BufferCount = 1;
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc.BufferDesc.Width = Width;
	SwapDesc.BufferDesc.Height = Height;
	SwapDesc.OutputWindow = hwnd;
	SwapDesc.Windowed = Windowed;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapDesc.SampleDesc.Count = 4;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &SwapDesc, &SwapChain, &Device, NULL, &Devcon);

	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Device And Swap Chain Failed!", "Error", MB_OKCANCEL);
		return;
	}

	ID3D11Texture2D* BackBuffer;
	this->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);

	hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTarget);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Render Target Failed!", "Error", MB_OKCANCEL);
	}
	UserInterface.emplace(this->Device, this->Devcon, this->hwnd, Width, Height);

	D3D11_TEXTURE2D_DESC DSD;
	ZeroMemory(&DSD, sizeof(D3D11_TEXTURE2D_DESC));

	DSD.Width = Width;
	DSD.Height = Height;
	DSD.ArraySize = 1;
	DSD.MipLevels = 1;
	DSD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DSD.SampleDesc.Quality = 0;
	DSD.SampleDesc.Count = 4;
	DSD.Usage = D3D11_USAGE_DEFAULT;
	DSD.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DSD.CPUAccessFlags = 0;
	DSD.MiscFlags = 0;

	hr = Device->CreateTexture2D(&DSD, NULL, &DepthStencilBuffer);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Texture 2d Failed!", "Error", MB_OKCANCEL);
	}

	hr = Device->CreateDepthStencilView(DepthStencilBuffer, NULL, &DepthStencilView);

	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Depth Stencil View Failed!", "Error", MB_OKCANCEL);
	}

	Devcon->OMSetRenderTargets(1, &RenderTarget, DepthStencilView);

	D3D11_DEPTH_STENCIL_DESC depthdesc = { 0 };
	depthdesc.DepthEnable = TRUE;
	depthdesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthdesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	hr = Device->CreateDepthStencilState(&depthdesc, &DepthStencilState);
	if (FAILED(hr))
	{
		MessageBoxA(this->hwnd, "Create Depth Stencil State Failed!", "Error", MB_OKCANCEL);
	}

	Devcon->OMSetDepthStencilState(DepthStencilState, 1);
	

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	Devcon->RSSetViewports(1, &vp);

	D3D11_RASTERIZER_DESC RD;
	ZeroMemory(&RD,sizeof(RD));
	RD.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	RD.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	RD.MultisampleEnable = TRUE;
	RD.AntialiasedLineEnable = TRUE;

	Device->CreateRasterizerState(&RD, &this->RasterState);
	Devcon->RSSetState(this->RasterState);
	RasterState->Release();

	if (!InitShaders()) 
	{
		return;
	}
	if (!InitObjects()) 
	{
		return;
	}
}

Renderer::~Renderer()
{
	UserInterface->Clean_UI();
	cube.Clean();
	this->Device->Release();
	this->Devcon->Release();
	this->SwapChain->Release();
	this->InputLayout->Release();
	this->ConstantBuffer->Release();
	this->RenderTarget->Release();
	this->VertexShader->Release();
	this->PixelShader->Release();
	this->RasterState->Release();
	this->DepthStencilView->Release();
	this->DepthStencilBuffer->Release();
	this->DepthStencilState->Release();
}

void Renderer::Render() 
{
	BeginFrame();
	cube.Render();
	UserInterface->Render_UI();
	Endframe();
}

void Renderer::BeginFrame()
{
	Devcon->ClearRenderTargetView(RenderTarget, bg);
	Devcon->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, NULL);
}

void Renderer::Endframe()
{
	this->SwapChain->Present(1, 0);
}
