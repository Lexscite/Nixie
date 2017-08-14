#include "Engine.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (CEngine::GetSingleton())
		return CEngine::GetSingleton()->MsgProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

CEngine::CEngine()
{
	m_hwnd = 0;
}

CEngine* CEngine::s_singleton;

CEngine* CEngine::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CEngine;

	return s_singleton;
}

void CEngine::Release()
{
	if (m_hwnd != nullptr)
		DestroyWindow(m_hwnd);

	safe_release(CGraphics::GetSingleton());
	safe_release(CConnection::GetSingleton());
}

bool CEngine::Init(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	m_WndTitle = "Nixie";
	m_wndStyle = WS_OVERLAPPEDWINDOW;

	m_vsyncEnabled = true;
	m_fullscreenEnabled = false;
	if (m_fullscreenEnabled)
	{
		m_screenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		m_screenWidth = 800;
		m_screenHeight = 600;
	}

	if (!CreateMainWindow())
	{
		MessageBox(m_hwnd, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!CGraphics::GetSingleton()->Init(m_screenWidth, m_screenHeight, m_vsyncEnabled, m_fullscreenEnabled))
		return false;

	if (!CConnection::GetSingleton()->Establish("127.0.0.1", 1111))
		MessageBox(m_hwnd, "Failed to conenct to server", "Network Error", MB_OK | MB_ICONERROR);
	else
	{
		if (CConnection::GetSingleton()->SendPacketType(PacketType::ChatMessage))
		{
			CConnection::GetSingleton()->SendString(std::string("Hi Server!"));
		}
	}

	return true;
}

bool CEngine::CreateMainWindow()
{
	WNDCLASSEX wcex;
	LPCSTR className = "MainWindowClass";

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hInstance;
	wcex.lpfnWndProc = MainWndProc;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;

	if (!RegisterClassEx(&wcex))
	{
		std::cerr << "Failed to register window class" << std::endl;
		return false;
	}

	UINT x, y;
	if (m_fullscreenEnabled)
	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<ULONG>(m_screenWidth);
		dmScreenSettings.dmPelsHeight = static_cast<ULONG>(m_screenHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		x = 0;
		y = 0;
	}
	else
	{
		x = GetSystemMetrics(SM_CXSCREEN) / 2 - m_screenWidth / 2;
		y = GetSystemMetrics(SM_CYSCREEN) / 2 - m_screenHeight / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, className, m_WndTitle, m_wndStyle,
		x, y, m_screenWidth, m_screenHeight, NULL, NULL, m_hInstance, NULL);
	if (!m_hwnd)
	{
		std::cerr << "Failed to create main window" << std::endl;
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOW);

	return true;
}

LRESULT CEngine::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

int CEngine::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Update(0.0f);
	}

	return static_cast<int>(msg.wParam);
}

void CEngine::Update(float deltaTime)
{
	CGraphics::GetSingleton()->Render();
}

HWND CEngine::GetHwnd()
{
	return m_hwnd;
}