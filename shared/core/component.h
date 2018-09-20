#ifndef NIXIE_COMPONENT_H_
#define NIXIE_COMPONENT_H_

#pragma once

#include "game_object.h"
#include "transform.h"
#include "scene.h"


namespace nixie
{
	class Transform;
	class Scene;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		virtual bool Init(std::shared_ptr<GameObject> game_object) final;
		virtual bool Update();

		std::string GetName();

		std::shared_ptr<Scene> GetScene();
		std::shared_ptr<GameObject> GetGameObject();
		std::shared_ptr<Transform> GetTransform();

	private:
		virtual bool OnInit();
		virtual bool OnUpdate();

	private:
		std::shared_ptr<GameObject> game_object_;
	};
}

#endif