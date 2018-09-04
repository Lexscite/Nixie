#ifndef NIXIE_SCENE_H_
#define NIXIE_SCENE_H_

#pragma once

#include "components/camera.h"


namespace Nixie
{
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