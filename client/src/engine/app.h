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
		static App* GetSingleton();

		bool Init(HINSTANCE instance);
		int Run();

		LRESULT MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

		HWND GetHwnd();
		D3D* GetDirectX();
		std::shared_ptr<Scene> GetScene();

	private:
		App();

		bool InitWindow(HINSTANCE instance);
		void InitSettings();
		void Update(float delta_time);

		void CalculateFrameStats();

		bool LoadScene(std::shared_ptr<Scene> scene);

	private:
		static App* singleton_;

		HWND window_;
		LPCSTR window_caption_;

		unsigned int screen_width_;
		unsigned int screen_height_;

		bool vsync_enabled_;
		bool fullscreen_enabled_;

		Time* time_;
		bool is_paused_;

		D3D* directx_;
		Input* input_;

		std::shared_ptr<Scene> scene_;
	};
}

#endif