#ifndef NIXIE_COMPONENT_H_
#define NIXIE_COMPONENT_H_

#pragma once

#include "../time.h"
#include "../graphics/d3d.h"
#include "../input/input.h"
#include "../math/math.h"

#include "game_object.h"


namespace Nixie
{
	class Transform;
	class GameObject;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		virtual void Init(std::shared_ptr<GameObject> game_object) final;
		virtual void Update();

		virtual std::string GetName() final;
		virtual std::shared_ptr<GameObject> GetGameObject() final;

		std::shared_ptr<Transform> GetTransform();

	private:
		virtual void OnInit();
		virtual void OnUpdate();

	private:
		std::shared_ptr<GameObject> game_object_;
	};
}

#endif