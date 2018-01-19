#ifndef SCENE_H
#define SCENE_H

#pragma once

#include <vector>
#include <iostream>

#include "components/camera.h"
#include "components/mesh.h"
#include "components/material.h"
#include "components/movement.h"

namespace Nixie
{
	class Component;

	class Scene final
	{
	public:
		Scene();

		bool Init();
		void Release();
		void Update();

		DirectX::SimpleMath::Color GetClearColor();
		Camera* GetCamera();

		bool AddGameObject(GameObject* new_game_object);
		GameObject* GetGameObject(std::string name);
		std::vector<GameObject*> GetGameObjects();

	private:
		void OutputDebugMessage();

	private:
		DirectX::SimpleMath::Color clear_color_;
		Camera* current_camera_;
		std::map<std::string, GameObject*> game_objects_;
	};
}

#endif