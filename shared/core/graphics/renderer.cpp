#include "../../stdafx_core.h"

#include "renderer.h"


namespace vodoo
{
	Renderer::Renderer() :
		device_(DirectXManager::Get()->GetDevice()),
		device_context_(DirectXManager::Get()->GetDeviceContext())
	{}


	Renderer& Renderer::Get()
	{
		static Renderer instance;
		return instance;
	}


	void Renderer::RenderMesh(std::shared_ptr<Mesh> mesh)
	{
		unsigned int stride = sizeof(VertexPTN);
		unsigned int offset = 0;

		auto vertex_buffer = mesh->GetVertexBuffer();
		auto index_buffer = mesh->GetIndexBuffer();

		device_context_->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		device_context_->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		device_context_->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	}
}