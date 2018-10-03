#ifndef VOODOO_APPLICATION_H_
#define VOODOO_APPLICATION_H_

#include <voodoo/directx_manager.h>
#include <voodoo/scene.h>
#include <voodoo/time.h>
#include "connection.h"

namespace voodoo
{
	class Application final
	{
	public:
		static bool Init(HINSTANCE instance);
		static int Run();

		static HWND GetWindow() { return window_; }
		static DirectXManager* GetDirectX() { return directx_; }
		static std::shared_ptr<Scene> GetScene() { return scene_; }

	private:
		static bool InitWindow(HINSTANCE instance);
		static void InitSettings();
		static bool Update(float delta_time);

		static void CalculateFrameStats();

		static bool LoadScene();

	protected:
		static LRESULT CALLBACK MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

	private:
		static HWND window_;
		static LPCWSTR window_caption_;

		static Time* time_;
		static DirectXManager* directx_;
		static std::shared_ptr<Scene> scene_;

		static unsigned int screen_width_;
		static unsigned int screen_height_;

		static bool vsync_enabled_;
		static bool fullscreen_enabled_;

		static bool is_paused_;
	};
}

#endif