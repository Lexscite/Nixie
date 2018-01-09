#include "game_object.h"

namespace Nixie
{
	GameObject::GameObject(std::string name) : 
		name(name),
		scene(nullptr),
		parent(nullptr),
		position(Vector3()),
		rotation(Quaternion()),
		scale(Vector3(1)) {}

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

		components.insert(std::pair<std::string, Component*>(name, new_component));
		return true;
	}

	Component* GameObject::GetComponent(std::string name)
	{
		std::map<std::string, Component*>::iterator result = components.find(name);
		if (result == components.end())
			return nullptr;
		else
			return result->second;
	}

	std::vector<Component*> GameObject::GetComponents()
	{
		std::vector<Component*> result;
		for (std::map<std::string, Component*>::iterator it = components.begin(); it != components.end(); ++it)
			result.push_back(it->second);

		return result;
	}

	std::string GameObject::GetName()
	{
		return name;
	}

	Vector3 GameObject::GetPosition()
	{
		if (parent == nullptr)
			return position;
		else
			return parent->GetPosition() + position;
	}

	Quaternion GameObject::GetRotation()
	{
		if (parent == nullptr)
			return rotation;
		else
			return rotation * parent->GetRotation();
	}

	Vector3 GameObject::GetScale()
	{
		if (parent == nullptr)
			return scale;
		else
			return parent->GetScale() + scale;
	}
}