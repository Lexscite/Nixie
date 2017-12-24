#include "Mesh.h"

Mesh::Mesh()
{
	m_pVertexBuffer = 0;
	m_pIndexBuffer = 0;
	m_meshData = 0;
}

bool Mesh::Init(char* filePath)
{
	if (!LoadFile(filePath))
	{
		return false;
		std::cerr << "Failed to load mesh" << std::endl;
	}

	if (!InitBuffers())
	{
		std::cerr << "Failed to load buffers" << std::endl;
		return false;
	}

	return true;
}

void Mesh::Release()
{
	safe_release(m_pIndexBuffer);
	safe_release(m_pVertexBuffer);
	safe_delete_arr(m_meshData);
}

bool Mesh::LoadFile(char* filePath)
{
	std::ifstream fin;
	fin.open(filePath);

	if (fin.fail())
		return false;

	char input;
	fin.get(input);
	while (input != ':')
		fin.get(input);

	fin >> m_vertexCount;

	m_indexCount = m_vertexCount;

	m_meshData = new ModelType[m_vertexCount];
	if (!m_meshData)
		return false;

	fin.get(input);
	while (input != ':')
		fin.get(input);
	fin.get(input);
	fin.get(input);

	for (size_t i = 0; i < m_vertexCount; i++)
	{
		fin >> m_meshData[i].x >> m_meshData[i].y >> m_meshData[i].z;
		fin >> m_meshData[i].nx >> m_meshData[i].ny >> m_meshData[i].nz;
	}

	fin.close();

	return true;
}

void Mesh::Render()
{
	RenderBuffers();
}

int Mesh::GetIndexCount()
{
	return m_indexCount;
}

bool Mesh::InitBuffers()
{
	m_vertexCount = 3;
	m_indexCount = 3;

	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	ULONG* indices = new ULONG[m_indexCount];
	if (!indices)
		return false;

	for  (size_t i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = Vector3(m_meshData[i].x, m_meshData[i].y, m_meshData[i].z);
		vertices[i].normal = Vector3(m_meshData[i].nx, m_meshData[i].ny, m_meshData[i].nz);

		indices[i] = (ULONG)i;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	ID3D11Device* device = D3D::GetSingleton()->GetDevice();
	HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);
	if (FAILED(result))
		return false;

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer);
	if (FAILED(result))
		return false;

	safe_delete_arr(vertices);
	safe_delete_arr(indices);

	return true;
}

void Mesh::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	ID3D11DeviceContext* deviceContext = D3D::GetSingleton()->GetDeviceContext();

	deviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}