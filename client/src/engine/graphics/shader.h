#ifndef NIXIE_SHADER_H_
#define NIXIE_SHADER_H_

#pragma once

#include "d3d.h"
#include "../math/color.h"
#include "../math/vector.h"
#include "../math/matrix.h"


namespace Nixie
{
	class Shader
	{
	private:
		struct MatrixBuffer
		{
			Matrix4x4<float> world_matrix;
			Matrix4x4<float> view_matrix;
			Matrix4x4<float> projection_matrix;
		};

		struct LightBuffer
		{
			Color diffuse_color;
			Color ambient_color;
			Vector3<float> direction;
			float padding;
		};

		struct PixelBuffer
		{
			Color color;
		};

	public:
		Shader();
		~Shader();

		bool Init(std::string vs_path, std::string ps_path, bool light);
		bool Update(const Matrix4x4<float>& world_matrix, ID3D11ShaderResourceView* texture);

	private:
		bool CreateVertexShader(std::vector<unsigned char*> buffer);
		bool CreateInputLayout(std::vector<unsigned char*> buffer);
		D3D11_INPUT_ELEMENT_DESC CreateInputElement(LPCSTR name, unsigned int index, DXGI_FORMAT format, unsigned int slot, unsigned int offset, D3D11_INPUT_CLASSIFICATION slot_class, unsigned int step_rate);
		bool CreateMatrixBuffer();

		bool CreatePixelShader(std::vector<unsigned char*> buffer);
		bool CreateSamplerState();
		bool CreateLightBuffer();

		std::vector<unsigned char*> LoadFromFile(std::string file_path);

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		ID3D11VertexShader* vertex_shader_;
		ID3D11PixelShader* pixel_shader_;
		ID3D11InputLayout* input_layout_;
		ID3D11SamplerState* sampler_state_;

		ID3D11Buffer* matrix_buffer_;
		ID3D11Buffer* light_buffer_;
		ID3D11Buffer* pixel_buffer_;

		bool light_;
	};
}

#endif