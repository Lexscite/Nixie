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

	Vector3 Component::GetPosition()
	{
		return game_object->GetPosition();
	}

	Quaternion Component::GetRotation()
	{
		return game_object->GetRotation();
	}

	Vector3 Component::GetScale()
	{
		return game_object->GetScale();
	}

	void Component::SetPosition(Vector3 value)
	{
		game_object->SetPosition(value);
	}

	void Component::SetRotation(Quaternion value)
	{
		game_object->SetRotation(value);
	}

	void Component::SetScale(Vector3 value)
	{
		game_object->SetScale(value);
	}

	void Component::Translate(Vector3 value)
	{
		game_object->Translate(value);
	}

	void Component::Rotate(Quaternion value)
	{
		game_object->Rotate(value);
	}

	void Component::Scale(Vector3 value)
	{
		game_object->Scale(value);
	}
}