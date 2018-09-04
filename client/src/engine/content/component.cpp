#include "../../stdafx.h"

#include "component.h"

namespace Nixie
{
	void Component::Init(GameObject* game_object)
	{
		this->game_object = game_object;

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
		return std::string(typeid(*this).name()).erase(0, 6 + 7);
	}

	GameObject* Component::GetGameObject()
	{
		return game_object;
	}

	Transform* Component::GetTransform()
	{
		return game_object->GetTransform();
	}
}