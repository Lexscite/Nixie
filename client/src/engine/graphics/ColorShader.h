#ifndef __COLORSHADER_H__
#define __COLORSHADER_H__

#pragma once

#include <fstream>
#include <string>

#include "DirectX.h"

using namespace DirectX;

class CColorShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	CColorShader();

	bool Init();
	void Release();
	bool Render(int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

private:
	bool InitShader(WCHAR*, WCHAR*);
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderPath);

	bool SetShaderParameters(XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void RenderShader(int indexCount);

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;
};

#endif