#pragma once

#include<d3d11.h>
#include"Matrix.h"

struct VERTEX
{
	Vector4 Pos;
	Vector3 Color;
};

class IRenderable
{
public:

	virtual bool Init(ID3D11Device* dev, ID3D11DeviceContext* Devcon, IDXGISwapChain* SwapChain) = 0;
	virtual Matrix4x4 GetModleMatrix() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

};