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
	return true;
}

void Input::Release()
{

}

bool Input::Update()
{
	keyboard_state_ = keyboard_->GetState();

	return true;
}

Keyboard::State Input::GetState()
{
	return keyboard_state_;
}