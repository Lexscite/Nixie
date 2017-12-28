#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H_

#pragma once

#include <map>
#include <vector>
#include <utility>

#include "../utils/memory.h"
#include "../math/color.h"
#include "../math/vector.h"
#include "component.h"

class Component;

class GameObject final
{
public:
	GameObject(std::string name);

	bool Init();
	void Update();
	void Release();

	bool AddComponent(Component* new_component);
	Component* GetComponent(std::string name);
	std::vector<Component*> GetComponents();

	std::string GetName();
	Vector3* GetPosition();
	void SetPosition(Vector3* value);
	Vector3* GetRotation();
	void SetRotation(Vector3* value);
	Vector3* GetScale();
	void SetScale(Vector3* value);

private:
	std::string name_;

	GameObject* parent_;

	Vector3* position_;
	Vector3* rotation_;
	Vector3* scale_;

	std::map<std::string, Component*> components_;
};

#endif