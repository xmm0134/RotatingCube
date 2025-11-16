#include "Cube.h"
#include"Math.h"

void Cube::SetUpMMatrix(Vector4 Translate, float Scale, float RotateX, float RotateY, float RotateZ)
{
	Matrix4x4 RotationXMatrix = Math::RotateX(RotateX);
	Matrix4x4 RotationYMatrix = Math::RotateY(RotateY);
	Matrix4x4 RotationZMatrix = Math::RotateZ(RotateZ);

	Matrix4x4 RotationMatirx = RotationXMatrix * RotationYMatrix * RotationZMatrix;

	Matrix4x4 TranslationMatrix = Math::Translate(Translate);
	Matrix4x4 ScalingMatrix = Math::Scale(Scale);

	this->ModelMatrix = ScalingMatrix * RotationMatirx * TranslationMatrix;
}

bool Cube::Init(ID3D11Device* dev, ID3D11DeviceContext* Devcon, IDXGISwapChain* SwapChain)
{
	if (dev == nullptr)
	{
		return false;
	}
	if (Devcon == nullptr)
	{
		return false;
	}
	if (SwapChain == nullptr)
	{
		return false;
	}

	this->Device = dev;
	this->Devcon = Devcon;
	this->SwapChain = SwapChain;



	unsigned int cubeIndices[] = {
		 0, 1, 2,
		 2, 3, 0,
		 
		 5, 4, 7,
		 7, 6, 5,
		 
		 4, 0, 3,
		 3, 7, 4,
		 
		 1, 5, 6,
		 6, 2, 1,
		 
		 4, 5, 1,
		 1, 0, 4,
		 
		 3, 2, 6,
		 6, 7, 3
	};

	
	VERTEX verticies[] =
	{
	{Vector4(-0.5f, -0.5f,  0.5, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},  // Red
	{Vector4(0.5f, -0.5f,  0.5f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)},  // Green
	{Vector4(0.5f,  0.5f,  0.5f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},  // Blue
	{Vector4(-0.5f,  0.5f,  0.5f, 1.0f), Vector3(1.0f, 1.0f, 0.0f)}, // Yellow

	{Vector4(-0.5f, -0.5f, -0.5f, 1.0f), Vector3(1.0f, 0.0f, 1.0f)}, // Magenta
	{Vector4(0.5f, -0.5f, -0.5f, 1.0f), Vector3(0.0f, 1.0f, 1.0f)},  // Cyan
	{Vector4(0.5f,  0.5f, -0.5f, 1.0f), Vector3(1.0f, 0.5f, 0.0f)},  // Orange
	{Vector4(-0.5f,  0.5f, -0.5f, 1.0f), Vector3(0.5f, 0.0f, 0.5f)}, // Purple
	};

	D3D11_BUFFER_DESC VertexBufferDesc;
	VertexBufferDesc.ByteWidth = ARRAYSIZE(verticies) * sizeof(VERTEX);
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = FALSE;
	VertexBufferDesc.MiscFlags = NULL;
	VertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA Verticiesdata;
	Verticiesdata.pSysMem = verticies;
	Verticiesdata.SysMemPitch = NULL;
	Verticiesdata.SysMemSlicePitch = NULL;

	this->Indicies_Count = ARRAYSIZE(cubeIndices);

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.ByteWidth = this->Indicies_Count * sizeof(unsigned int);
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = FALSE;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.StructureByteStride = NULL;
	BufferDesc.MiscFlags = FALSE;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = cubeIndices;
	data.SysMemPitch = NULL;
	data.SysMemSlicePitch = NULL;

	HRESULT hr = this->Device->CreateBuffer(&BufferDesc, &data, &this->IndexBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	hr = this->Device->CreateBuffer(&VertexBufferDesc, &Verticiesdata, &this->Buffer);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

Matrix4x4 Cube::GetModleMatrix()
{
	return this->ModelMatrix;
}

void Cube::Render()
{
	this->Devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->Devcon->IASetVertexBuffers(NULL, 1, &this->Buffer, &this->Stride, &this->Offset);
	this->Devcon->IASetIndexBuffer(this->IndexBuffer, DXGI_FORMAT_R32_UINT, NULL);
	this->Devcon->DrawIndexed(this->Indicies_Count, NULL, NULL);
}

void Cube::Clean()
{
	this->Buffer->Release();
	this->IndexBuffer->Release();
}

void Cube::Scale(float Factor)
{
	this->ModelMatrix * Math::Scale(Factor);
}

void Cube::RotateZ(float Theta)
{
	this->ModelMatrix * Math::RotateZ(Theta);
}

void Cube::RotateX(float Theta)
{
	this->ModelMatrix* Math::RotateX(Theta);
}

void Cube::RotateY(float Theta)
{
	this->ModelMatrix* Math::RotateY(Theta);
}

void Cube::Translate(Vector3 Displacement)
{
	this->ModelMatrix* Math::Translate(Vector4(Displacement.x, Displacement.y, Displacement.z, 1.0f));
}