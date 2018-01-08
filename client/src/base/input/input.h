#ifndef INPUT_H
#define INPUT_H

#pragma once

#include <memory>
#include <map>

#include "../graphics/d3d.h"
#include "keyboard.h"

namespace Nixie
{
	class Input
	{
	public:
		static Input* GetSingleton();

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