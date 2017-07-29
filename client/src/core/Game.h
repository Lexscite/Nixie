#ifndef GAME_H
#define GAME_H

#include "graphics/Graphics.h"
#include "network/Client.h"

using NXGraphics::Graphics;
using NXNetwork::Client;
using NXNetwork::PacketType;

class Game
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	int Run();

	bool Init();
	void Release();
	void Update(float deltaTime);
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	bool CreateMainWindow();

protected:
	HWND m_hMainWnd;
	HINSTANCE m_hAppInstance;

	DWORD m_WndStyle;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	LPCSTR m_WndTitle;

	Graphics* m_pGraphics;
	bool m_Fullscreen;

	Client* m_pClient;
};

#endif // !GAME_H