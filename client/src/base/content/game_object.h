#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once

#include "../utils/memory.h"
#include "component.h"

namespace Nixie
{
	class Component;

	class GameObject final
	{
	public:
		GameObject(std::string name);

		bool Init();
		void Update();
		void Release();

		bool AddComponent(Component* new_component);
		Component* GetComponent(std::string name);
		std::vector<Component*> GetComponents();

		std::string GetName();

		DirectX::SimpleMath::Vector3 GetPosition();
		void SetPosition(DirectX::SimpleMath::Vector3 value);
		DirectX::SimpleMath::Vector3 GetRotation();
		void SetRotation(DirectX::SimpleMath::Vector3 value);
		DirectX::SimpleMath::Vector3 GetScale();
		void SetScale(DirectX::SimpleMath::Vector3 value);

		void Translate(DirectX::SimpleMath::Vector3 value);
		void Rotate(DirectX::SimpleMath::Vector3 value);

	private:
		std::string name_;

		GameObject* parent_;

		DirectX::SimpleMath::Vector3 position_;
		DirectX::SimpleMath::Vector3 rotation_;
		DirectX::SimpleMath::Vector3 scale_;

		std::map<std::string, Component*> components_;
	};
}

#endif