#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <typeinfo>

#include "../time.h"
#include "../graphics/d3d.h"
#include "../input/input.h"
#include "../math/vector3.h"

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

		Vector3 GetPosition();
		void SetPosition(Vector3 value);
		Vector3 GetRotation();
		void SetRotation(Vector3 value);
		Vector3 GetScale();
		void SetScale(Vector3 value);

		void Translate(Vector3 value);
		void Rotate(Vector3 value);

	private:
		virtual void OnInit();
		virtual void OnUpdate();

	private:
		GameObject* game_object_;
	};
}

#endif