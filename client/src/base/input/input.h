#ifndef INPUT_H
#define INPUT_H

#pragma once

#include <memory>
#include <map>

#include "../graphics/d3d.h"
#include "keyboard.h"

class Input
{
public:
	static Input* GetSingleton();

	bool Init();
	void Release();
	bool Update();

	Keyboard::State GetState();

	static bool IsKeyDown(Keyboard::Keys key);
	static bool Input::IsKeyPressed(Keyboard::Keys key);

private:
	Input();

private:
	static Input* singleton_;

	std::unique_ptr<Keyboard> keyboard_;
	Keyboard::State keyboard_state_prev_;
	Keyboard::State keyboard_state_;
};

#endif