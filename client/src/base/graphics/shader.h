#ifndef COLORSHADER_H
#define COLORSHADER_H

#pragma once

#include <fstream>
#include <string>

#include "d3d.h"

using namespace DirectX;

class Shader
{
private:
	struct MatrixBuffer
	{
		Matrix world_matrix;
		Matrix view_matrix;
		Matrix projection_matrix;
	};

	struct LightBuffer
	{
		Color diffuse_color;
		Vector3 direction;
		float padding;
	};

public:
	Shader();

	bool Init(WCHAR* vs_path, WCHAR* ps_path);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void Release();

	bool Update(Matrix world_matrix, Matrix view_matrix, Matrix projection_matrix);

private:
	bool InitVS(WCHAR* file_path);
	bool InitPS(WCHAR* file_path);

	void OutputShaderErrorMessage(ID3D10Blob* error_message, WCHAR* shader_path);

private:
	ID3D11VertexShader * vertex_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* layout_;
	ID3D11SamplerState* sampler_state_;

	ID3D11Buffer* matrix_buffer_;
	ID3D11Buffer* light_buffer_;
};

#endif