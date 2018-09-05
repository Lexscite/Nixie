#ifndef NIXIE_SHADER_H_
#define NIXIE_SHADER_H_

#pragma once

#include "d3d.h"


namespace Nixie
{
	class Shader
	{
	private:

		struct MatrixBuffer
		{
			DirectX::SimpleMath::Matrix world_matrix;
			DirectX::SimpleMath::Matrix view_matrix;
			DirectX::SimpleMath::Matrix projection_matrix;
		};

		struct LightBuffer
		{
			DirectX::SimpleMath::Color diffuse_color;
			DirectX::SimpleMath::Color ambient_color;
			DirectX::SimpleMath::Vector3 direction;
			float padding;
		};

	public:
		Shader();

		bool Init(std::string vs_path, std::string ps_path);
		void SetTexture(ID3D11ShaderResourceView* texture);
		void Release();

		bool Update(DirectX::SimpleMath::Matrix world_matrix);

	private:
		bool InitVS(std::vector<unsigned char*> shader_data);
		bool InitPS(std::vector<unsigned char*> shader_data);

		std::vector<unsigned char*> ReadCSO(std::string file_path);

	private:
		ID3D11VertexShader* vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11SamplerState* sampler_state;

		ID3D11Buffer* matrix_buffer;
		ID3D11Buffer* light_buffer;
	};
}

#endif