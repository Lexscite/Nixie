#include "game_object.h"

namespace Nixie
{
	GameObject::GameObject(std::string name)
	{
		name_ = name;

		parent_ = nullptr;

		position_ = DirectX::SimpleMath::Vector3();
		rotation_ = DirectX::SimpleMath::Vector3();
		scale_ = DirectX::SimpleMath::Vector3(1);
	}

	bool GameObject::Init(Scene* scene)
	{
		this->scene = scene;
		for each (Component* component in GetComponents())
			component->Init(this);

		return true;
	}

	void GameObject::Update()
	{
		for each (Component* component in GetComponents())
			component->Update();
	}

	void GameObject::Release()
	{
		for each (Component* component in GetComponents())
			safe_delete(component);
	}

	bool GameObject::AddComponent(Component* new_component)
	{
		std::string name = new_component->GetName();

		if (GetComponent(name) != nullptr)
			return false;

		components_.insert(std::pair<std::string, Component*>(name, new_component));
		return true;
	}

	Component* GameObject::GetComponent(std::string name)
	{
		std::map<std::string, Component*>::iterator result = components_.find(name);
		if (result == components_.end())
			return nullptr;
		else
			return result->second;
	}

	std::vector<Component*> GameObject::GetComponents()
	{
		std::vector<Component*> result;

		for (std::map<std::string, Component*>::iterator it = components_.begin(); it != components_.end(); ++it)
			result.push_back(it->second);

		return result;
	}

	std::string GameObject::GetName()
	{
		return name_;
	}

	DirectX::SimpleMath::Vector3 GameObject::GetPosition()
	{
		if (parent_ == nullptr)
			return position_;
		else
			return parent_->GetPosition() + position_;
	}

	void GameObject::SetPosition(DirectX::SimpleMath::Vector3 value)
	{
		position_ = value;
	}

	DirectX::SimpleMath::Vector3 GameObject::GetRotation()
	{
		if (parent_ == nullptr)
			return rotation_;
		else
			return parent_->GetRotation() + rotation_;
	}

	void GameObject::SetRotation(DirectX::SimpleMath::Vector3 value)
	{
		rotation_ = value;
	}

	DirectX::SimpleMath::Vector3 GameObject::GetScale()
	{
		if (parent_ == nullptr)
			return scale_;
		else
			return parent_->GetScale() + scale_;
	}

	void GameObject::SetScale(DirectX::SimpleMath::Vector3 value)
	{
		scale_ = value;
	}

	void GameObject::Translate(DirectX::SimpleMath::Vector3 value)
	{
		position_ += value;
	}

	void GameObject::Rotate(DirectX::SimpleMath::Vector3 value)
	{
		rotation_ += value;
	}
}