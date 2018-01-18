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
#include "../math/quaternion.h"

#include "game_object.h"

namespace Nixie
{
	class Transform;

	class GameObject;

	class Component
	{
	public:
		virtual void Init(GameObject* game_object) final;
		virtual void Update();

		virtual std::string GetName() final;
		virtual GameObject* GetGameObject() final;

		Transform* GetTransform();

	private:
		virtual void OnInit();
		virtual void OnUpdate();

	private:
		GameObject* game_object;
	};
}

#endif