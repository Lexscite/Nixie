#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once

#include "../utils/memory.h"
#include "component.h"

namespace Nixie
{
	class Scene;
	class Component;

	class Transform
	{
	public:
		Transform() :
			position(Vector3()),
			rotation(Quaternion()),
			scale(Vector3(1)) {}

		Vector3 GetUp() { return Vector3::Up().Rotate(rotation); }
		Vector3 GetDown() { return Vector3::Down().Rotate(rotation); }
		Vector3 GetLeft() { return Vector3::Left().Rotate(rotation); }
		Vector3 GetRight() { return Vector3::Right().Rotate(rotation); }
		Vector3 GetForward() { return Vector3::Forward().Rotate(rotation); }
		Vector3 GetBackward() { return Vector3::Backward().Rotate(rotation); }

		Vector3 GetPosition() { return position; }
		Quaternion GetRotation() { return rotation.Normalize(); }
		Vector3 GetScale() { return scale; }

		inline void SetPosition(Vector3 v) { position = v; }
		inline void SetRotation(Quaternion q) { rotation = q; }
		inline void SetScale(Vector3 v) { scale = v; }

		inline void Translate(Vector3 v) { this->position += v; }
		inline void Rotate(Quaternion q) { this->rotation *= q; }
		inline void Scale(Vector3 v) { this->scale += v; }

	private:
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
	};

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