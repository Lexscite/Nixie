#include "Game.h"

namespace
{
	Game* g_pGame = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pGame)
		return g_pGame->MsgProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

Game::Game(HINSTANCE hInstance)
{
	g_pGame = this;

	m_hAppInstance = hInstance;
	m_hMainWnd = NULL;

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

	m_pGraphics = nullptr;
	m_pClient = nullptr;
}

Game::~Game()
{
	if (m_hMainWnd != nullptr)
	{
		DestroyWindow(m_hMainWnd);
	}

	if (m_pGraphics)
	{
		delete m_pGraphics;
		m_pGraphics = nullptr;
	}

	if (m_pClient)
	{
		delete m_pClient;
		m_pClient = nullptr;
	}
}

bool Game::Init()
{
	if (!CreateMainWindow())
	{
		cerr << "Failed to create window" << endl;
		return false;
	}

	m_pGraphics = new Graphics;
	if (!m_pGraphics)
		return false;

	if (!m_pGraphics->Init(m_hMainWnd, m_ClientWidth, m_ClientHeight, m_Fullscreen))
		return false;

	cout << "Network initialization..." << endl;
	m_pClient = new Client;
	if (!m_pClient)
		return false;

	if (!m_pClient->Init("127.0.0.1", 1111))
		return false;
	cout << "OK" << endl;

	cout << "Connecting to server..." << endl;
	if (!m_pClient->Connect())
	{
		cerr << "Failed to connect to server" << endl;
		MessageBox(m_hMainWnd, "Failed to conenct to server", "Network Error", MB_OK | MB_ICONERROR);
	}
	else
		cout << "OK" << endl;

	m_pClient->SendPacketType(PacketType::ChatMessage);
	m_pClient->SendString(string("Hi Server!"));

	return true;
}

bool Game::CreateMainWindow()
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
		cerr << "Failed to register window class" << endl;
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
		cerr << "Failed to create main window" << endl;
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);

	return true;
}

LRESULT Game::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

int Game::Run()
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

void Game::Update(float deltaTime)
{
	m_pGraphics->Render();
}