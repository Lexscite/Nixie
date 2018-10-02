#ifndef vodoo_SCENE_H_
#define vodoo_SCENE_H_

#pragma once

#include "math/color.h"


namespace vodoo
{
	class GameObject;
	class Camera;

	class Scene final : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();

		bool Init();
		bool Update();

		Color GetClearColor() { return clear_color_; }
		std::shared_ptr<Camera> GetCamera() { return camera_; }
		void SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

		bool AddGameObject(std::shared_ptr<GameObject> new_game_object);
		std::shared_ptr<GameObject> GetGameObject(std::string name);
		std::vector<std::shared_ptr<GameObject>> GetGameObjects();

	private:
		Color clear_color_;
		std::shared_ptr<Camera> camera_;
		std::map<std::string, std::shared_ptr<GameObject>> game_objects_;
	};
}

#endif