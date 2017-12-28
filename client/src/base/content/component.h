#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <typeinfo>
#include <string>

#include "game_object.h"

class GameObject;

class Component
{
public:
	virtual void Init(GameObject* game_object) final;
	virtual void AfterInit();
	virtual void Update() final;

	virtual std::string GetName() final;
	virtual GameObject* GetGameObject() final;

private:
	virtual void OnInit();
	virtual void OnUpdate();

private:
	GameObject* game_object_;
};

#endif