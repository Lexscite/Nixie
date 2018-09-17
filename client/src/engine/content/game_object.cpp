#include "../../stdafx.h"

#include "game_object.h"


namespace nixie
{
	GameObject::GameObject(std::string name) : 
		name_(name),
		scene_(nullptr),
		parent_(nullptr),
		transform_(new Transform(std::shared_ptr<GameObject>(this))) {}


	bool GameObject::Init(std::shared_ptr<Scene> scene)
	{
		this->scene_ = scene;
		for (auto component : GetComponents())
		{
			component->Init(shared_from_this());
		}

		return true;
	}


	bool GameObject::Update()
	{
		for (auto& component : GetComponents())
		{
			if (!component->Update())
			{
				return false;
			}
		}

		return true;
	}


	bool GameObject::AddComponent(std::shared_ptr<Component> new_component)
	{
		std::string name = new_component->GetName();

		if (GetComponent(name) != nullptr)
		{
			return false;
		}

		components_.insert(std::pair<std::string, std::shared_ptr<Component>>(name, new_component));

		return true;
	}


	std::shared_ptr<Component> GameObject::GetComponent(std::string name)
	{
		auto result = components_.find(name);
		
		if (result == components_.end())
		{
			return nullptr;
		}
		else
		{
			return result->second;
		}
	}


	std::vector<std::shared_ptr<Component>> GameObject::GetComponents()
	{
		std::vector<std::shared_ptr<Component>> result;

		for (auto& it : components_)
		{
			result.push_back(it.second);
		}

		return result;
	}
}