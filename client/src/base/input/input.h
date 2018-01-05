#ifndef INPUT_H
#define INPUT_H

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>

#include "../graphics/d3d.h"

class Input
{
public:
	static Input* GetSingleton();

	bool Init(HINSTANCE instance, HWND window, int screen_width, int screen_height);
	void Release();
	bool Update();

	Vector2 GetMouseLocation();

	bool IsButtonPressed(BYTE button);

private:
	Input();

	bool UpdateKeyboard();
	bool UpdateMouse();
	void NormalizeMousePosition();

private:
	static Input* singleton_;

	IDirectInput8* direct_input_;
	IDirectInputDevice8* mouse_;
	IDirectInputDevice8* keyboard_;

	unsigned char keyboard_state_[256];
	DIMOUSESTATE mouse_state_;

	int screen_width_, screen_height_;
	int mouse_x_, mouse_y_;
};

#endif