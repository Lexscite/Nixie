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

Vector3 * Component::GetPosition()
{
	return game_object_->GetPosition();
}

void Component::SetPosition(Vector3 * value)
{
	game_object_->SetPosition(value);
}

Vector3 * Component::GetRotation()
{
	return game_object_->GetRotation();
}

void Component::SetRotation(Vector3 * value)
{
	game_object_->SetRotation(value);
}

Vector3 * Component::GetScale()
{
	return game_object_->GetScale();
}

void Component::SetScale(Vector3 * value)
{
	game_object_->SetScale(value);
}

void Component::Translate(Vector3 * value)
{
	game_object_->Translate(value);
}