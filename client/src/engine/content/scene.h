#ifndef SCENE_H
#define SCENE_H

#pragma once

#include "components/camera.h"
#include "components/mesh.h"
#include "components/material.h"
#include "components/movement.h"
#include "components/terrain.h"

namespace Nixie
{
	class Component;

	class Scene final
	{
	public:
		Scene();

		bool Init();
		void Update();

		Color GetClearColor();
		Camera* GetCamera();

		bool AddGameObject(GameObject* new_game_object);
		GameObject* GetGameObject(std::string name);
		std::vector<GameObject*> GetGameObjects();

	private:
		Color clear_color;
		Camera* current_camera;
		std::map<std::string, GameObject*> game_objects;
	};
}

#endif