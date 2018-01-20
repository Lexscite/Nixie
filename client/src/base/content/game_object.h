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
		Transform() : position(Vector3()), rotation(Quaternion()), scale(Vector3(1)) {}

		Vector3 GetUp() { return Vector3::Up().Rotate(rotation); }
		Vector3 GetDown() { return Vector3::Down().Rotate(rotation); }
		Vector3 GetLeft() { return Vector3::Left().Rotate(rotation); }
		Vector3 GetRight() { return Vector3::Right().Rotate(rotation); }
		Vector3 GetForward() { return Vector3::Forward().Rotate(rotation); }
		Vector3 GetBackward() { return Vector3::Backward().Rotate(rotation); }

		Vector3 GetPosition() { return position; }
		Quaternion GetRotation() { return rotation; }
		Vector3 GetScale() { return scale; }

		inline void SetPosition(float x, float y, float z) { position = Vector3(x, y, z); }
		inline void SetPosition(Vector3 v) { position = v; }

		inline void SetRotation(float r, float p, float y) { rotation = Quaternion(r, p, y); }
		inline void SetRotation(Vector3 v) { rotation = Quaternion(v); }

		inline void SetScale(float value) { scale = Vector3(value); }
		inline void SetScale(float x, float y, float z) { scale = Vector3(x, y, z); }
		inline void SetScale(Vector3 v) { scale = v; }

		inline void Translate(float x, float y, float z) { position += Vector3(x, y, z); }
		inline void Translate(Vector3 v) { position += v; }

		inline void Rotate(float r, float p, float y) { rotation *= Quaternion(r, p, y); }
		inline void Rotate(Vector3 v) { rotation *= Quaternion(v); }

		inline void Scale(float value) { scale += Vector3(value); }
		inline void Scale(float x, float y, float z) { scale += Vector3(x, y, z); }
		inline void Scale(Vector3 v) { scale += v; }

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