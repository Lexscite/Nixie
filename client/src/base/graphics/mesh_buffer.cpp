#include "mesh_buffer.h"

namespace Nixie
{
	bool MeshBuffer::Init(unsigned long vertex_count, unsigned long index_count, Vertex* vertices, unsigned long* indices)
	{
		HRESULT hr;

		ID3D11Device* device = D3D::GetSingleton()->GetDevice();

		D3D11_BUFFER_DESC vertex_buffer_desc;
		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(Vertex) * vertex_count;
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertex_buffer_data;
		vertex_buffer_data.pSysMem = vertices;
		vertex_buffer_data.SysMemPitch = 0;
		vertex_buffer_data.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC index_buffer_desc;
		index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		index_buffer_desc.ByteWidth = sizeof(unsigned long) * index_count;
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;
		index_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA index_data;
		index_data.pSysMem = indices;
		index_data.SysMemPitch = 0;
		index_data.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
		if (FAILED(hr))
			return false;

		safe_delete_arr(indices);

		return true;
	}

	void MeshBuffer::Release()
	{
		safe_release(index_buffer);
		safe_release(vertex_buffer);
	}

	void MeshBuffer::Render(unsigned long index_count, D3D11_PRIMITIVE_TOPOLOGY format)
	{
		ID3D11DeviceContext* device_context = D3D::GetSingleton()->GetDeviceContext();
		unsigned int stride = sizeof(Vertex);
		unsigned int offset = 0;

		device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		device_context->IASetPrimitiveTopology(format);

		device_context->DrawIndexed(index_count, 0, 0);

	}
}