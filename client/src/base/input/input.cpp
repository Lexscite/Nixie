#include "input.h"

Input::Input()
{
	direct_input_ = nullptr;
	keyboard_ = nullptr;
	mouse_ = nullptr;
}

Input* Input::singleton_;

Input* Input::GetSingleton()
{
	if (singleton_ == nullptr)
		singleton_ = new Input;

	return singleton_;
}

bool Input::Init(HINSTANCE instance, HWND window, int screen_width, int screen_height)
{
	HRESULT hr;

	screen_width_ = screen_width;
	screen_height_ = screen_height;

	mouse_x_ = 0;
	mouse_y_ = 0;

	hr = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&direct_input_, NULL);
	if (FAILED(hr))
		return false;

	hr = direct_input_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	if (FAILED(hr))
		return false;

	hr = keyboard_->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return false;

	hr = keyboard_->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
		return false;

	hr = keyboard_->Acquire();
	if (FAILED(hr))
		return false;

	hr = direct_input_->CreateDevice(GUID_SysMouse, &mouse_, NULL);
	if (FAILED(hr))
		return false;

	hr = mouse_->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
		return false;

	hr = mouse_->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		return false;

	hr = mouse_->Acquire();
	if (FAILED(hr))
		return false;

	return true;
}

void Input::Release()
{
	mouse_->Unacquire();
	safe_release(mouse_);

	keyboard_->Unacquire();
	safe_release(keyboard_);

	safe_release(direct_input_);
}

bool Input::Update()
{
	if (!UpdateKeyboard())
		return false;

	if (!UpdateMouse())
		return false;

	return true;
}

bool Input::UpdateKeyboard()
{
	HRESULT hr;

	hr = keyboard_->GetDeviceState(sizeof(keyboard_state_), (LPVOID)&keyboard_state_);
	if (FAILED(hr))
	{
		if ((hr = DIERR_INPUTLOST) || (hr = DIERR_NOTACQUIRED))
			keyboard_->Acquire();
		else
			return false;
	}

	return true;
}

bool Input::UpdateMouse()
{
	HRESULT hr;

	hr = mouse_->GetDeviceState(sizeof(mouse_state_), (LPVOID)&mouse_state_);
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
			mouse_->Acquire();
		else
			return false;
	}

	return true;
}

void Input::NormalizeMousePosition()
{
	mouse_x_ += mouse_state_.lX;
	mouse_y_ += mouse_state_.lY;

	if (mouse_x_ < 0)
		mouse_x_ = 0;
	if (mouse_y_ < 0)
		mouse_y_ = 0;

	if (mouse_x_ > screen_width_)
		mouse_x_ = screen_width_;
	if (mouse_y_ > screen_height_)
		mouse_y_ = screen_height_;
}

Vector2 Input::GetMouseLocation()
{
	NormalizeMousePosition();

	return Vector2(static_cast<float>(mouse_x_), static_cast<float>(mouse_y_));
}

bool Input::IsButtonPressed(BYTE button)
{
	if (keyboard_state_[button] & 0x80)
		return true;
	else
		return false;
}