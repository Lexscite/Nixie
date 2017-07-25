#include "Graphics.h"

namespace NixieClient
{
	Graphics::Graphics()
	{
		m_pDirectX = nullptr;
	}

	Graphics::~Graphics()
	{
		SafeDelete(m_pDirectX);
	}

	bool Graphics::Init(HWND hwnd, int clientWidth, int clientHeight, bool fullscreen)
	{
		m_Fullscreen = fullscreen;

		m_pDirectX = new DirectX;
		if (!m_pDirectX->Init(hwnd, clientWidth, clientHeight, true, m_Fullscreen, 1000.0f, 0.1f))
		{
			MessageBox(NULL, "DirectX initialization failed", "Error", MB_OK);
			OutputDebugString("DirectX initialization failed");
			return false;
		}

		return true;
	}

	void Graphics::Render()
	{
		m_pDirectX->Render();
	}
}