#include "../stdafx.h"

#include "app.h"
#include "log.h"


namespace Nixie
{
	LRESULT CALLBACK WindowProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
	{
		if (App::GetSingleton())
			return App::GetSingleton()->MessageProcessor(window, message, w_param, l_param);
		else
			return DefWindowProc(window, message, w_param, l_param);
	}


	App::App()
	{
		input_ = nullptr;
		directx_ = nullptr;
		time_ = nullptr;
		scene_ = nullptr;
		is_paused_ = false;
	}

	
	App* App::singleton_;


	App* App::GetSingleton()
	{
		if (singleton_ == 0)
			singleton_ = new App;

		return singleton_;
	}


	bool App::Init(HINSTANCE instance)
	{
		input_ = Input::GetSingleton();
		directx_ = D3D::GetSingleton();
		time_ = Time::GetSingleton();

		InitSettings();

		if (!InitWindow(instance))
		{
			MessageBox(window_, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
			Log::GetInstance().Write("Failed to initialize window");
			return false;
		}
		else
		{
			Log::GetInstance().Write("Window initialized");
		}

		if (!input_->Init())
		{
			MessageBox(window_, "Failed to initialize input system", "Error", MB_OK | MB_ICONERROR);
			Log::GetInstance().Write("Failed to initialize input");
			return false;
		}
		else
		{
			Log::GetInstance().Write("Input initialized");
		}

		if (!directx_->Init(screen_width_, screen_height_, vsync_enabled_, fullscreen_enabled_, 1000.0f, 0.1f))
		{
			MessageBox(window_, "DirectX initialization failed", "Error", MB_OK | MB_ICONERROR);
			Log::GetInstance().Write("Failed to initialize DirectX");
			return false;
		}
		else
		{
			Log::GetInstance().Write("DirectX initialized");
		}

		//if (!CConnection::GetSingleton()->Establish("127.0.0.1", 1111))
		//{
		//	MessageBox(m_hwnd, "Failed to conenct to server", "Network Error", MB_OK | MB_ICONERROR);
		//	return false;
		//}
		//else
		//	if (CConnection::GetSingleton()->SendPacketType(PacketType::HelloMessage))
		//		CConnection::GetSingleton()->SendString(std::string("Hi Server!"));

		if (!LoadScene(std::make_shared<Scene>()))
		{
			Log::GetInstance().Write("Failed to load scene");
			return false;
		}
		else
		{
			Log::GetInstance().Write("Scene loaded");
		}

		return true;
	}
	

	void App::InitSettings()
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


	bool App::InitWindow(HINSTANCE instance)
	{
		WNDCLASSEX wc;
		LPCSTR class_name = "MainWindowClass";
		window_caption_ = "Nixie";
		DWORD style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbClsExtra = NULL;
		wc.cbWndExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = instance;
		wc.lpfnWndProc = WindowProcessor;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = class_name;

		if (!RegisterClassEx(&wc))
			return false;

		int window_pos_x, window_pos_y;
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

			window_pos_x = 0;
			window_pos_y = 0;
		}
		else
		{
			window_pos_x = GetSystemMetrics(SM_CXSCREEN) / 2 - screen_width_ / 2;
			window_pos_y = GetSystemMetrics(SM_CYSCREEN) / 2 - screen_height_ / 2;
		}

		window_ = CreateWindowEx(WS_EX_APPWINDOW, class_name, window_caption_, style,
			window_pos_x, window_pos_y, screen_width_, screen_height_, NULL, NULL, instance, NULL);
		if (!window_)
		{
			Log::GetInstance().Write("WINAPI CreateWindowEx failed");
			return false;
		}

		ShowWindow(window_, SW_SHOW);

		return true;
	}


	LRESULT App::MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MOVE:
			if (LOWORD(w_param) == WM_MOVING)
			{
				is_paused_ = true;
				time_->Stop();
			}
			else
			{
				is_paused_ = false;
				time_->Start();
			}
			return 0;
		case WM_MENUCHAR:
			return MAKELRESULT(0, MNC_CLOSE);
		case WM_GETMINMAXINFO:
			((MINMAXINFO*)l_param)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)l_param)->ptMinTrackSize.y = 200;
			return 0;
		case WM_ACTIVATEAPP:
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			DirectX::Keyboard::ProcessMessage(message, w_param, l_param);
			return 0;
		default:
			return DefWindowProc(window, message, w_param, l_param);
		}
	}


	int App::Run()
	{
		time_->Reset();

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				time_->Tick();
				if (!is_paused_)
				{
#ifdef _DEBUG
					CalculateFrameStats();
#endif
					if (!Update(0.0f))
					{
						// Temporary exit code
						return 404;
					}
				}
				else
					Sleep(100);
			}
		}

		return static_cast<int>(msg.wParam);
	}


	bool App::Update(float delta_time)
	{
		if (!input_->Update())
		{
			return false;
		}

		directx_->BeginScene(scene_->GetClearColor());

		if (!scene_->Update())
		{
			return false;
		}

		directx_->EndScene();

		return true;
	}


	HWND App::GetHwnd()
	{
		return window_;
	}

	D3D* App::GetDirectX()
	{
		return directx_;
	}

	std::shared_ptr<Scene> App::GetScene()
	{
		return scene_;
	}

	void App::CalculateFrameStats()
	{
		static int frame_count = 0;
		static float time_elapsed = 0;

		frame_count++;

		if ((time_->GetTime() - time_elapsed) >= 1)
		{
			float fps = static_cast<float>(frame_count);
			float ms_per_frame = 1000 / fps;

			std::wostringstream window_caption;
			window_caption.precision(6);
			window_caption << window_caption_ << " | FPS: " << fps << " Frame time: " << ms_per_frame << "ms";
			SetWindowTextW(window_, static_cast<LPCWSTR>(window_caption.str().c_str()));
			frame_count = 0;
			time_elapsed++;
		}
	}

	bool App::LoadScene(std::shared_ptr<Scene> scene)
	{
		if (!scene->Init())
			return false;

		scene_ = scene;

		return true;
	}
}