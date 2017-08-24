#ifndef __ENGINE_H__
#define __ENGINE_H__

#pragma once

#include "graphics\Graphics.h"
#include "network\Connection.h"
#include "world\Scene.h"

class CEngine
{
public:
	static CEngine* GetSingleton();

	bool Init(HINSTANCE hInstance);
	void Release();
	int Run();
	void Update(float deltaTime);
	
	HWND GetHwnd();

	bool LoadScene(CScene* scene);

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	CEngine();

	bool CreateMainWindow();

private:
	static CEngine* s_singleton;

	HWND m_hwnd;
	HINSTANCE m_hInstance;

	DWORD m_wndStyle;
	UINT m_screenWidth;
	UINT m_screenHeight;
	LPCSTR m_WndTitle;

	bool m_vsyncEnabled;
	bool m_fullscreenEnabled;

	CScene* m_currentScene;
};

#endif