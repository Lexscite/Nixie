#include "../../stdafx.h"

#include "game_object.h"


namespace Nixie
{
	GameObject::GameObject(std::string name) : 
		name(name),
		scene(nullptr),
		parent(nullptr),
		transform(new Transform) {}


	bool GameObject::Init(std::shared_ptr<Scene> scene)
	{
		this->scene = scene;
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

		components.insert(std::pair<std::string, std::shared_ptr<Component>>(name, new_component));

		return true;
	}


	std::shared_ptr<Component> GameObject::GetComponent(std::string name)
	{
		auto result = components.find(name);
		
		if (result == components.end())
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

		for (auto& it : components)
		{
			result.push_back(it.second);
		}

		return result;
	}


	std::string GameObject::GetName()
	{
		return name;
	}


	std::shared_ptr<Transform> GameObject::GetTransform()
	{
		return transform;
	}
}