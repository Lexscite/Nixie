#include "component.h"

void Component::Init(GameObject* game_object)
{
	game_object_ = game_object;
	OnInit();
}

void Component::AfterInit() {}

void Component::OnInit() {}

void Component::Update()
{
	OnUpdate();
}

void Component::OnUpdate() {}

std::string Component::GetName()
{
	std::string name = std::string(typeid(*this).name());

	return name.erase(0, 6);
}

GameObject* Component::GetGameObject()
{
	return game_object_;
}