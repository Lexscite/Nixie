#ifndef NIXIE_GAME_OBJECT_H_
#define NIXIE_GAME_OBJECT_H_

#pragma once

#include "transform.h"
#include "component.h"


namespace Nixie
{
	class Scene;
	class Component;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(std::string name);

		bool Init(std::shared_ptr<Scene> scene);
		bool Update();

		bool AddComponent(std::shared_ptr<Component> new_component);
		std::shared_ptr<Component> GetComponent(std::string name);
		std::vector<std::shared_ptr<Component>> GetComponents();

		std::string GetName();
		std::shared_ptr<Transform> GetTransform();

	private:
		std::string name;
		std::shared_ptr<Scene> scene;
		std::shared_ptr<GameObject> parent;
		std::shared_ptr<Transform> transform;
		std::map<std::string, std::shared_ptr<Component>> components;
	};
}

#endif