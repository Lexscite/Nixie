#include "Engine.h"

LRESULT CALLBACK WindowProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	if (Engine::GetSingleton())
		return Engine::GetSingleton()->MessageProcessor(window, message, w_param, l_param);
	else
		return DefWindowProc(window, message, w_param, l_param);
}

Engine::Engine()
{
	window_ = 0;
}

Engine* Engine::singleton_;

Engine* Engine::GetSingleton()
{
	if (singleton_ == 0)
		singleton_ = new Engine;

	return singleton_;
}

void Engine::Release()
{
	if (window_ != nullptr)
		DestroyWindow(window_);

	safe_release(Graphics::GetSingleton());
	//safe_release(CConnection::GetSingleton());
}

bool Engine::Init(HINSTANCE instance)
{
	instance_ = instance;

	InitSettings();

	if (!CreateMainWindow())
	{
		MessageBox(window_, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!Graphics::GetSingleton()->Init(screen_width_, screen_height_, vsync_enabled_, fullscreen_enabled_))
		return false;

	//if (!CConnection::GetSingleton()->Establish("127.0.0.1", 1111))
	//{
	//	MessageBox(m_hwnd, "Failed to conenct to server", "Network Error", MB_OK | MB_ICONERROR);
	//	return false;
	//}
	//else
	//	if (CConnection::GetSingleton()->SendPacketType(PacketType::HelloMessage))
	//		CConnection::GetSingleton()->SendString(std::string("Hi Server!"));

	Scene* start_scene = new Scene;
	if (!LoadScene(start_scene))
		return false;

	return true;
}

void Engine::InitSettings()
{
	vsync_enabled_ = true;
	fullscreen_enabled_ = false;
	if (fullscreen_enabled_)
	{
		screen_width_ = GetSystemMetrics(SM_CXSCREEN);
		screen_height_ = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		screen_width_ = 800;
		screen_height_ = 600;
	}
}

bool Engine::CreateMainWindow()
{
	WNDCLASSEX wc;
	LPCSTR class_name = "MainWindowClass";
	LPCSTR title = "Nixie";
	DWORD style = WS_OVERLAPPEDWINDOW | WS_THICKFRAME;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = instance_;
	wc.lpfnWndProc = WindowProcessor;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = class_name;

	if (!RegisterClassEx(&wc))
		return false;

	UINT x, y;
	if (fullscreen_enabled_)
	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<ULONG>(screen_width_);
		dmScreenSettings.dmPelsHeight = static_cast<ULONG>(screen_height_);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		x = 0;
		y = 0;
	}
	else
	{
		x = GetSystemMetrics(SM_CXSCREEN) / 2 - screen_width_ / 2;
		y = GetSystemMetrics(SM_CYSCREEN) / 2 - screen_height_ / 2;
	}

	window_ = CreateWindowEx(WS_EX_APPWINDOW, class_name, title, style,
		x, y, screen_width_, screen_height_, NULL, NULL, instance_, NULL);
	if (!window_)
	{
		std::cerr << "Failed to create main window" << std::endl;
		return false;
	}

	ShowWindow(window_, SW_SHOW);

	return true;
}

LRESULT Engine::MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(window, message, w_param, l_param);
	}
}

int Engine::Run()
{
	MSG message = { 0 };
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
			Update(0.0f);
	}

	return static_cast<int>(message.wParam);
}

void Engine::Update(float delta_time)
{
	current_scene_->Update();
	Graphics::GetSingleton()->Render();
}

HWND Engine::GetHwnd()
{
	return window_;
}

bool Engine::LoadScene(Scene* scene)
{
	if (!scene->Init())
		return false;

	current_scene_ = scene;

	return true;
}

Scene* Engine::GetCurrentScene()
{
	return current_scene_;
}