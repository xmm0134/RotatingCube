#pragma once

#include"Renderable.h"
#include"Matrix.h"

class Cube : public IRenderable
{
private:
	ID3D11Buffer* Buffer;
	ID3D11Buffer* IndexBuffer;

	ID3D11Device* Device;
	ID3D11DeviceContext* Devcon;
	IDXGISwapChain* SwapChain;
	UINT Stride = sizeof(VERTEX);
	UINT Offset = NULL;
	UINT Indicies_Count;

	Matrix4x4 ModelMatrix;

public:
	void SetUpMMatrix(Vector4 Translate, float Scale, float RotateX, float RotateY, float RotateZ);
	bool Init(ID3D11Device* dev, ID3D11DeviceContext* Devcon, IDXGISwapChain* SwapChain) override;
	Matrix4x4 GetModleMatrix() override;
	void Render() override;
	void Clean() override;
	void Scale(float Factor);
	void RotateZ(float Theta);
	void RotateX(float Theta);
	void RotateY(float Theta);
	void Translate(Vector3 Displacement);

private:
	
};