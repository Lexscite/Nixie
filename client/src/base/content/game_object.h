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
		Quaternion GetRotation();
		Vector3 GetScale();

		void SetPosition(Vector3 value);
		void SetRotation(Quaternion value);
		void SetScale(Vector3 value);

		void Translate(Vector3 value);
		void Rotate(Quaternion value);
		void Scale(Vector3 value);

	private:
		std::string name;

		Scene* scene;
		GameObject* parent;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		std::map<std::string, Component*> components;
	};

	inline void GameObject::SetPosition(Vector3 value)
	{
		position = value;
	}

	inline void GameObject::SetRotation(Quaternion value)
	{
		rotation = value;
	}

	inline void GameObject::SetScale(Vector3 value)
	{
		scale = value;
	}

	inline void GameObject::Translate(Vector3 value)
	{
		position += value;
	}

	inline void GameObject::Rotate(Quaternion value)
	{
		rotation *= value.Normalize();
	}

	inline void GameObject::Scale(Vector3 value)
	{
		scale += value;
	}
}

#endif