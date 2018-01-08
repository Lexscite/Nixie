#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once

#include "../utils/memory.h"
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

		Vector3 GetPosition();
		void SetPosition(Vector3 value);
		Vector3 GetRotation();
		void SetRotation(Vector3 value);
		Vector3 GetScale();
		void SetScale(Vector3 value);

		void Translate(Vector3 value);
		void Rotate(Vector3 value);

	private:
		std::string name_;

		Scene* scene;
		GameObject* parent_;

		Vector3 position_;
		Vector3 rotation_;
		Vector3 scale_;

		std::map<std::string, Component*> components_;
	};
}

#endif