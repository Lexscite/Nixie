#include "component.h"

namespace Nixie
{
	void Component::Init(GameObject* game_object)
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
		std::string name = std::string(typeid(*this).name());

		return name.erase(0, 6 + 7);
	}

	GameObject* Component::GetGameObject()
	{
		return game_object_;
	}

	DirectX::SimpleMath::Vector3 Component::GetPosition()
	{
		return game_object_->GetPosition();
	}

	void Component::SetPosition(DirectX::SimpleMath::Vector3 value)
	{
		game_object_->SetPosition(value);
	}

	DirectX::SimpleMath::Vector3 Component::GetRotation()
	{
		return game_object_->GetRotation();
	}

	void Component::SetRotation(DirectX::SimpleMath::Vector3 value)
	{
		game_object_->SetRotation(value);
	}

	DirectX::SimpleMath::Vector3 Component::GetScale()
	{
		return game_object_->GetScale();
	}

	void Component::SetScale(DirectX::SimpleMath::Vector3 value)
	{
		game_object_->SetScale(value);
	}

	void Component::Translate(DirectX::SimpleMath::Vector3 value)
	{
		game_object_->Translate(value);
	}

	void Component::Rotate(DirectX::SimpleMath::Vector3 value)
	{
		game_object_->Rotate(value);
	}
}