#include "../stdafx_core.h"

#include "component.h"


namespace vodoo
{
	bool Component::Init(std::shared_ptr<GameObject> game_object)
	{
		game_object_ = game_object;


		if (!OnInit())
		{
			return false;
		}

		return true;
	}


	bool Component::OnInit()
	{
		return true;
	}


	bool Component::Update()
	{
		if (!OnUpdate())
		{
			return false;
		}

		return true;
	}


	bool Component::OnUpdate()
	{
		return true;
	}


	std::string Component::GetName()
	{
		return std::string(typeid(*shared_from_this()).name()).erase(0, 6 + 7);
	}


	std::shared_ptr<Scene> Component::GetScene()
	{
		return game_object_->GetScene();
	}


	std::shared_ptr<GameObject> Component::GetGameObject()
	{
		return game_object_;
	}


	std::shared_ptr<Transform> Component::GetTransform()
	{
		return game_object_->GetTransform();
	}
}