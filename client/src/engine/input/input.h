#ifndef NIXIE_INPUT_H_
#define NIXIE_INPUT_H_

#pragma once

#include "keyboard.h"


namespace Nixie
{
	class Input
	{
	public:
		static Input* Get();

		bool Init();
		void Release();
		bool Update();

		DirectX::Keyboard::State GetState();

		static bool IsKeyDown(DirectX::Keyboard::Keys key);
		static bool Input::IsKeyPressed(DirectX::Keyboard::Keys key);

	private:
		Input();

	private:
		static Input* singleton_;

		std::unique_ptr<DirectX::Keyboard> keyboard_;
		DirectX::Keyboard::State keyboard_state_prev_;
		DirectX::Keyboard::State keyboard_state_;
	};
}

#endif