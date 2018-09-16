#ifndef NIXIE_APP_H_
#define NIXIE_APP_H_

#pragma once

#include "network/connection.h"
#include "content/scene.h"
#include "time.h"


namespace Nixie
{
	class App final
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

		static bool LoadScene(std::shared_ptr<Scene> scene);

	protected:
		static LRESULT CALLBACK MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

	private:
		static HWND window_;
		static LPCSTR window_caption_;

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