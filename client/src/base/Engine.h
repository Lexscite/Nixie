#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include "graphics\Graphics.h"
#include "network\Connection.h"
#include "world\Scene.h"

class Engine
{
public:
	static Engine* GetSingleton();

	HWND GetHwnd();

	bool Init(HINSTANCE instance);
	void Release();
	int Run();

	Scene* GetCurrentScene();

	LRESULT MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

private:
	Engine();

	bool InitWindow();
	void InitSettings();
	bool Update(float delta_time);
	bool LoadScene(Scene* scene);

private:
	static Engine* singleton_;

	HWND window_;
	HINSTANCE instance_;

	UINT screen_width_;
	UINT screen_height_;

	bool vsync_enabled_;
	bool fullscreen_enabled_;

	Scene* current_scene_;
};

#endif