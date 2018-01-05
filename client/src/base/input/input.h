#ifndef INPUT_H
#define INPUT_H

#pragma once

#include <memory>

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

private:
	Input();

private:
	static Input* singleton_;

	std::unique_ptr<Keyboard> keyboard_;
	Keyboard::State keyboard_state_;
};

#endif