#ifndef SCENE_H
#define SCENE_H

#pragma once

#include <vector>
#include <iostream>

#include "game_object.h"
#include "components/camera.h"
#include "components/mesh.h"
#include "components/material.h"

class Scene final
{
public:
	Scene();

	bool Init();
	void Release();
	void Update();

	Color* GetClearColor();
	Camera* GetCamera();
	std::vector<GameObject*> GetGameObjects();

private:
	void OutputDebugMessage();

private:
	Color* clear_color_;
	Camera* current_camera_;
	std::vector<GameObject*> game_objects_;
};

#endif