#ifndef GAME_H
#define GAME_H

#include "graphics/Graphics.h"
#include "network/Connection.h"

class CSystem
{
public:
	static CSystem* GetSingleton();

	bool Init(HINSTANCE hInstance);
	void Release();
	int Run();
	void Update(float deltaTime);

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	CSystem();

	bool CreateMainWindow();

private:
	static CSystem* s_singleton;

	HWND m_hMainWnd;
	HINSTANCE m_hAppInstance;

	DWORD m_WndStyle;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	LPCSTR m_WndTitle;

	bool m_Fullscreen;
};

#endif