#ifndef NIXIE_SCENE_H_
#define NIXIE_SCENE_H_

#pragma once

#include "components/camera.h"


namespace Nixie
{
	class Scene final : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();

		bool Init();
		void Update();

		Color GetClearColor();
		std::shared_ptr<Camera> GetCamera();

		bool AddGameObject(std::shared_ptr<GameObject> new_game_object);
		std::shared_ptr<GameObject> GetGameObject(std::string name);
		std::vector<std::shared_ptr<GameObject>> GetGameObjects();

	private:
		Color clear_color;
		std::shared_ptr<Camera> current_camera;
		std::map<std::string, std::shared_ptr<GameObject>> game_objects;
	};
}

#endif