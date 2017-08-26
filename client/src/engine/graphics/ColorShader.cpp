#include "ColorShader.h"
#include "..\Engine.h"

CColorShader::CColorShader()
{
	m_pVertexShader = 0;
	m_pPixelShader = 0;
	m_pLayout = 0;
	m_pMatrixBuffer = 0;
}

bool CColorShader::Init()
{
	if (!InitShader(L"../../../client/src/content/shaders/color.vs", L"../../../Client/src/content/shaders/Color.ps"))
		return false;

	return true;
}

void CColorShader::Release()
{
	safe_release(m_pMatrixBuffer);
	safe_release(m_pLayout);
	safe_release(m_pPixelShader);
	safe_release(m_pVertexShader);
}

bool CColorShader::Render(int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	if (!SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix))
		return false;

	RenderShader(indexCount);

	return true;
}

bool CColorShader::InitShader(WCHAR* vsPath, WCHAR* psPath)
{
	ID3D10Blob* vertexShaderBuffer = 0;
	ID3D10Blob* errorMessage = 0;
	HRESULT result = D3DCompileFromFile(vsPath, 0, 0, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, vsPath);
		else
			MessageBox(CEngine::GetSingleton()->GetHwnd(), (LPCSTR)vsPath, "Missing Shader File", MB_OK);

		return false;
	}

	ID3D10Blob* pixelShaderBuffer = 0;
	result = D3DCompileFromFile(psPath, 0, 0, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, psPath);
		}
		else
		{
			MessageBox(CEngine::GetSingleton()->GetHwnd(), (LPCSTR)psPath, "Missing Shader File", MB_OK);
		}

		return false;
	}

	ID3D11Device* device = CDirectX::GetSingleton()->GetDevice();
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), 0, &m_pVertexShader);
	if (FAILED(result))
		return false;

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);
	if (FAILED(result))
		return false;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_pLayout);
	if (FAILED(result))
		return false;

	safe_release(vertexShaderBuffer);
	safe_release(pixelShaderBuffer);

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_pMatrixBuffer);
	if (FAILED(result))
		return false;

	return true;
}

void CColorShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderPath)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	std::ofstream fout;


	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i<bufferSize; i++)
		fout << compileErrors[i];

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(CEngine::GetSingleton()->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", (LPCSTR)shaderPath, MB_OK);
}

bool CColorShader::SetShaderParameters(XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11DeviceContext* deviceContext = CDirectX::GetSingleton()->GetDeviceContext();
	HRESULT result = deviceContext->Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		return false;

	MatrixBufferType* dataPtr;
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	deviceContext->Unmap(m_pMatrixBuffer, 0);
	
	UINT bufferNumber = 0;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_pMatrixBuffer);

	return true;
}

void CColorShader::RenderShader(int indexCount)
{
	ID3D11DeviceContext* deviceContext = CDirectX::GetSingleton()->GetDeviceContext();
	deviceContext->IASetInputLayout(m_pLayout);
	deviceContext->VSSetShader(m_pVertexShader, 0, 0);
	deviceContext->PSSetShader(m_pPixelShader, 0, 0);
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}