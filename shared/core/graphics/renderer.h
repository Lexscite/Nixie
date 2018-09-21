#ifndef NIXIE_RENDERER_H_
#define NIXIE_RENDERER_H_

#pragma once

#include "directx_manager.h"
#include "mesh.h"


namespace nixie
{
	class Renderer
	{
	public:
		static Renderer& Get();

		void RenderMesh(std::shared_ptr<Mesh> mesh);

	private:
		Renderer();

		ID3D11Device* device_;
		ID3D11DeviceContext* device_context_;
	};
}

#endif