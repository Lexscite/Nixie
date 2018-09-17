#ifndef NIXIE_COMPONENT_H_
#define NIXIE_COMPONENT_H_

#pragma once

#include "../time.h"
#include "../graphics/directx_manager.h"
#include "../input/input.h"
#include "../math/math.h"

#include "game_object.h"


namespace nixie
{
	class Transform;
	class GameObject;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		virtual bool Init(std::shared_ptr<GameObject> game_object) final;
		virtual bool Update();

		virtual std::string GetName() final;
		virtual std::shared_ptr<GameObject> GetGameObject() final;

		std::shared_ptr<Transform> GetTransform();

	private:
		virtual bool OnInit();
		virtual bool OnUpdate();

	private:
		std::shared_ptr<GameObject> game_object_;
	};
}

#endif