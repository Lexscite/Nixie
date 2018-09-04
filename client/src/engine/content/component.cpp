#include "../../stdafx.h"

#include "component.h"

namespace Nixie
{
	void Component::Init(std::shared_ptr<GameObject> game_object)
	{
		game_object_ = game_object;

		OnInit();
	}

	void Component::OnInit() {}

	void Component::Update()
	{
		OnUpdate();
	}

	void Component::OnUpdate() {}

	std::string Component::GetName()
	{
		return std::string(typeid(*shared_from_this()).name()).erase(0, 6 + 7);
	}

	std::shared_ptr<GameObject> Component::GetGameObject()
	{
		return game_object_;
	}

	std::shared_ptr<Transform> Component::GetTransform()
	{
		return game_object_->GetTransform();
	}
}