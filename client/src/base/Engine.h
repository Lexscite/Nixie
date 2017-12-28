#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include "network/connection.h"
#include "content/scene.h"

class Engine final
{
public:
	static Engine* GetSingleton();

	bool Init(HINSTANCE instance);
	void Release();
	int Run();

	LRESULT MessageProcessor(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

	HWND GetHwnd();
	D3D* GetDirectX();
	Scene* GetScene();

private:
	Engine();

	bool InitWindow(HINSTANCE instance);
	void InitSettings();
	void Update(float delta_time);
	bool LoadScene(Scene* scene);

private:
	static Engine* singleton_;

	HWND window_;

	IntVector2* resolution_;
	bool vsync_enabled_;
	bool fullscreen_enabled_;

	D3D* directx_;
	Scene* scene_;
};

#endif