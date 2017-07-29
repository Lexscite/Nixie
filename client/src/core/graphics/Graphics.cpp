#include "Graphics.h"

namespace NXGraphics
{
	Graphics::Graphics()
	{
		m_pDirectX = nullptr;
	}

	Graphics::~Graphics()
	{
		if (m_pDirectX)
		{
			delete m_pDirectX;
			m_pDirectX = nullptr;
		}
	}

	bool Graphics::Init(HWND hwnd, int clientWidth, int clientHeight, bool fullscreen)
	{
		m_Fullscreen = fullscreen;

		cout << "DirectX iniitialization..." << endl;
		m_pDirectX = new DirectX;
		if (!m_pDirectX->Init(hwnd, clientWidth, clientHeight, true, m_Fullscreen, 1000.0f, 0.1f))
		{
			cerr << "Failed to initialize DirectX" << endl;
			MessageBox(hwnd, "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
			return false;
		}
		cout << "OK" << endl;

		return true;
	}

	void Graphics::Render()
	{
		m_pDirectX->Render();
	}
}