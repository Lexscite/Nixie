#include "input.h"

Input::Input()
{
	keyboard_ = std::make_unique<Keyboard>();
}

Input* Input::singleton_;

Input* Input::GetSingleton()
{
	if (singleton_ == nullptr)
		singleton_ = new Input;

	return singleton_;
}

bool Input::Init()
{
	keyboard_state_ = keyboard_->GetState();

	return true;
}

void Input::Release()
{

}

bool Input::Update()
{
	keyboard_state_prev_ = keyboard_state_;
	keyboard_state_ = keyboard_->GetState();

	return true;
}

Keyboard::State Input::GetState()
{
	return keyboard_state_;
}

bool Input::IsKeyDown(Keyboard::Keys key)
{
	return Input::GetSingleton()->keyboard_state_.IsKeyDown(key);
}

bool Input::IsKeyPressed(Keyboard::Keys key)
{
	if (!Input::GetSingleton()->keyboard_state_prev_.IsKeyDown(key))
		return Input::GetSingleton()->keyboard_state_.IsKeyDown(key);
	else
		return false;
}