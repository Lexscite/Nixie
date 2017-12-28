#include "game_object.h"

GameObject::GameObject()
{
	position_ = new Vector3();
	rotation_ = new Vector3();
	scale_ = new Vector3(1, 1, 1);
	parent_ = nullptr;
}

bool GameObject::Init()
{
	std::vector<Component*> components = GetComponents();
	for each (Component* component in components)
		component->Init(this);
	for each (Component* component in components)
		component->AfterInit();

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

std::vector<Component*> GameObject::GetComponents()
{
	std::vector<Component*> result;

	for (std::map<std::string, Component*>::iterator it = components_.begin(); it != components_.end(); ++it)
		result.push_back(it->second);

	return result;
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

Vector3* GameObject::GetPosition()
{
	if (parent_ == nullptr)
		return position_;
	else
		return Vector3::Sum(parent_->GetPosition(), position_);
}

void GameObject::SetPosition(Vector3* value)
{
	position_ = value;
}

Vector3* GameObject::GetRotation()
{
	if (parent_ == nullptr)
		return rotation_;
	else
		return Vector3::Sum(parent_->GetRotation(), rotation_);
}

void GameObject::SetRotation(Vector3* value)
{
	rotation_ = value;
}

Vector3* GameObject::GetScale()
{
	if (parent_ == nullptr)
		return scale_;
	else
		return Vector3::Sum(parent_->GetScale(), scale_);
}

void GameObject::SetScale(Vector3* value)
{
	scale_ = value;
}