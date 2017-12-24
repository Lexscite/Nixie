#ifndef COLORSHADER_H
#define COLORSHADER_H

#pragma once

#include <fstream>
#include <string>

#include "D3D.h"

using namespace DirectX;

class ColorShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ColorShader();

	bool Init();
	void Release();
	bool Render(int index_count, XMMATRIX world_matrix, XMMATRIX view_matrix, XMMATRIX projection_matrix);

private:
	bool InitShader(WCHAR*, WCHAR*);
	void OutputShaderErrorMessage(ID3D10Blob* error_message, WCHAR* shader_path);

	bool SetShaderParameters(XMMATRIX world_matrix, XMMATRIX view_matrix, XMMATRIX projection_matrix);
	void RenderShader(int index_count);

private:
	ID3D11VertexShader* vertex_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* layout_;
	ID3D11Buffer* matrix_buffer_;
};

#endif