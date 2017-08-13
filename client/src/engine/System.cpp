#include "System.h"

CSystem* CSystem::s_singleton;

CSystem* CSystem::GetSingleton()
{
	if (s_singleton == 0)
		s_singleton = new CSystem;

	return s_singleton;
}

CSystem::CSystem()
{
	m_hMainWnd = 0;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (CSystem::GetSingleton())
		return CSystem::GetSingleton()->MsgProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CSystem::Release()
{
	if (m_hMainWnd != nullptr)
		DestroyWindow(m_hMainWnd);

	safe_release(CGraphics::GetSingleton());
	safe_release(CConnection::GetSingleton());
}

bool CSystem::Init(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;
	m_WndTitle = "Nixie";
	m_WndStyle = WS_OVERLAPPEDWINDOW;

	m_Fullscreen = false;
	if (m_Fullscreen)
	{
		m_ClientWidth = GetSystemMetrics(SM_CXSCREEN);
		m_ClientHeight = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		m_ClientWidth = 800;
		m_ClientHeight = 600;
	}

	if (!CreateMainWindow())
	{
		std::cerr << "Failed to create window" << std::endl;
		return false;
	}

	if (!CGraphics::GetSingleton()->Init(m_hMainWnd, m_ClientWidth, m_ClientHeight, m_Fullscreen))
		return false;

	std::cout << "Connecting to server... " << std::endl;
	if (!CConnection::GetSingleton()->Init("127.0.0.1", 1111))
		MessageBox(m_hMainWnd, "Failed to conenct to server", "Network Error", MB_OK | MB_ICONERROR);
	std::cout << "OK" << std::endl;

	CConnection::GetSingleton()->SendPacketType(PacketType::ChatMessage);
	CConnection::GetSingleton()->SendString(std::string("Hi Server!"));

	return true;
}

bool CSystem::CreateMainWindow()
{
	WNDCLASSEX wcex;
	LPCSTR className = "MainWindowClass";

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hAppInstance;
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
	if (m_Fullscreen)
	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<ULONG>(m_ClientWidth);
		dmScreenSettings.dmPelsHeight = static_cast<ULONG>(m_ClientHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		x = 0;
		y = 0;
	}
	else
	{
		x = GetSystemMetrics(SM_CXSCREEN) / 2 - m_ClientWidth / 2;
		y = GetSystemMetrics(SM_CYSCREEN) / 2 - m_ClientHeight / 2;
	}

	m_hMainWnd = CreateWindowEx(WS_EX_APPWINDOW, className, m_WndTitle, m_WndStyle,
		x, y, m_ClientWidth, m_ClientHeight, NULL, NULL, m_hAppInstance, NULL);
	if (!m_hMainWnd)
	{
		std::cerr << "Failed to create main window" << std::endl;
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);

	return true;
}

LRESULT CSystem::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

int CSystem::Run()
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

void CSystem::Update(float deltaTime)
{
	CGraphics::GetSingleton()->Render();
}