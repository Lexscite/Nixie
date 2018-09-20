#include "../stdafx_core.h"

#include "scene.h"

#include "game_object.h"
#include "transform.h"


namespace nixie
{
	Scene::Scene() :
		clear_color_(Color(100, 100, 100))
	{}


	bool Scene::Init()
	{
		for (auto& game_object : GetGameObjects())
		{
			if (!game_object->Init(shared_from_this()))
			{
				return false;
			}
		}

		return true;
	}


	bool Scene::Update()
	{
		for (auto& game_object : GetGameObjects())
		{
			if (!game_object->Update())
			{
				return false;
			}
		}

		return true;
	}


	bool Scene::AddGameObject(std::shared_ptr<GameObject> new_game_object)
	{
		std::string name = new_game_object->GetName();

		if (GetGameObject(name) != nullptr)
		{
			return false;
		}

		game_objects_.insert(std::pair<std::string, std::shared_ptr<GameObject>>(name, new_game_object));

		return true;
	}


	std::shared_ptr<GameObject> Scene::GetGameObject(std::string name)
	{
		auto result = game_objects_.find(name);

		if (result == game_objects_.end())
		{
			return nullptr;
		}
		else
		{
			return result->second;
		}
	}


	std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects()
	{
		std::vector<std::shared_ptr<GameObject>> result;

		for (auto& it : game_objects_)
		{
			result.push_back(it.second);
		}

		return result;
	}
}