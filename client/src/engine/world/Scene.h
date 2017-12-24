#ifndef SCENE_H
#define SCENE_H

#pragma once

#include <vector>

#include "../math/Color.h"
#include "../graphics/Camera.h"
#include "../utils/Memory.h"
#include "../math/Vector.h"
#include "GameObject.h"

class Scene
{
public:
	bool Init();
	void Release();
	void Update();

	Color* GetClearColor();

private:
	Color* clear_color_;
	std::vector<GameObject*> game_objects_;
};

#endif