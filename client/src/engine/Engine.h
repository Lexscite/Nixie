#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "graphics/Graphics.h"
#include "network/Connection.h"

class CEngine
{
public:
	static CEngine* GetSingleton();

	bool Init(HINSTANCE hInstance);
	void Release();
	int Run();
	void Update(float deltaTime);

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	CEngine();

	bool CreateMainWindow();

private:
	static CEngine* s_singleton;

	HWND m_hMainWnd;
	HINSTANCE m_hAppInstance;

	DWORD m_WndStyle;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	LPCSTR m_WndTitle;

	bool m_Fullscreen;
};

#endif