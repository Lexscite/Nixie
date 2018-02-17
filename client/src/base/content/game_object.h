#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once

#include "../utils/memory.h"
#include "transform.h"
#include "component.h"

namespace Nixie
{
	class Scene;
	class Component;

	class GameObject final
	{
	public:
		GameObject(std::string name);

		bool Init(Scene* scene);
		void Update();
		void Release();

		bool AddComponent(Component* new_component);
		Component* GetComponent(std::string name);
		std::vector<Component*> GetComponents();

		std::string GetName();
		Transform* GetTransform();

	private:
		std::string name;
		Scene* scene;
		GameObject* parent;
		Transform* transform;
		std::map<std::string, Component*> components;
	};
}

#endif