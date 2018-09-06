#include "../../stdafx.h"

#include "input.h"


namespace Nixie
{
	Input::Input()
	{
		keyboard_ = std::make_unique<DirectX::Keyboard>();
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


	DirectX::Keyboard::State Input::GetState()
	{
		return keyboard_state_;
	}


	bool Input::IsKeyDown(DirectX::Keyboard::Keys key)
	{
		return Input::GetSingleton()->keyboard_state_.IsKeyDown(key);
	}


	bool Input::IsKeyPressed(DirectX::Keyboard::Keys key)
	{
		if (!Input::GetSingleton()->keyboard_state_prev_.IsKeyDown(key))
			return Input::GetSingleton()->keyboard_state_.IsKeyDown(key);
		else
			return false;
	}
}