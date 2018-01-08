#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <typeinfo>

#include "../graphics/d3d.h"
#include "../input/input.h"
#include "../time.h"
#include "game_object.h"

namespace Nixie
{
	class GameObject;

	class Component
	{
	public:
		virtual void Init(GameObject* game_object) final;
		virtual void Update();

		virtual std::string GetName() final;
		virtual GameObject* GetGameObject() final;

		DirectX::SimpleMath::Vector3 GetPosition();
		void SetPosition(DirectX::SimpleMath::Vector3 value);
		DirectX::SimpleMath::Vector3 GetRotation();
		void SetRotation(DirectX::SimpleMath::Vector3 value);
		DirectX::SimpleMath::Vector3 GetScale();
		void SetScale(DirectX::SimpleMath::Vector3 value);

		void Translate(DirectX::SimpleMath::Vector3 value);
		void Rotate(DirectX::SimpleMath::Vector3 value);

	private:
		virtual void OnInit();
		virtual void OnUpdate();

	private:
		GameObject* game_object_;
	};
}

#endif