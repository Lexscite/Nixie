#include "../../stdafx.h"

#include "scene.h"
#include "components/model.h"
#include "components/material.h"


namespace Nixie
{
	Scene::Scene() :
		clear_color(Color())
	{}


	bool Scene::Init()
	{
		std::shared_ptr<GameObject> ground = std::make_shared<GameObject>("Ground");
		ground->AddComponent(std::make_shared<Mesh>("../data/meshes/test_level_00_ground.txt"));
		ground->AddComponent(std::make_shared<Material>(L"../data/textures/grass.jpg"));
		AddGameObject(ground);

		std::shared_ptr<GameObject> crates = std::make_shared<GameObject>("Crates");
		crates->AddComponent(std::make_shared<Mesh>("../data/meshes/test_level_00_crates.txt"));
		crates->AddComponent(std::make_shared<Material>(L"../data/textures/crate.jpg"));
		AddGameObject(crates);

		std::shared_ptr<GameObject> box = std::make_shared<GameObject>("Box");
		box->AddComponent(std::make_shared<Mesh>("../data/meshes/cube.txt"));
		box->AddComponent(std::make_shared<Material>(L"../data/textures/placeholder.jpg"));
		box->GetTransform()->SetPosition(0, 0.5f, 0);
		AddGameObject(box);

		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>("Camera");
		camera->AddComponent(std::make_shared<Camera>());
		camera->GetTransform()->SetPosition(0, 12.0f, -8.0f);
		camera->GetTransform()->SetRotation(1.0f, 0, 0);
		current_camera = std::static_pointer_cast<Camera>(camera->GetComponent("Camera"));
		AddGameObject(camera);

		for (auto& game_object : GetGameObjects())
		{
			if (!game_object->Init(shared_from_this()))
			{
				return false;
			}
		}

		return true;
	}


	void Scene::Update()
	{
		current_camera->Render();

		for (auto& game_object : GetGameObjects())
		{
			game_object->Update();
		}
	}


	Color Scene::GetClearColor()
	{
		return clear_color;
	}


	std::shared_ptr<Camera> Scene::GetCamera()
	{
		return current_camera;
	}


	bool Scene::AddGameObject(std::shared_ptr<GameObject> new_game_object)
	{
		std::string name = new_game_object->GetName();

		if (GetGameObject(name) != nullptr)
		{
			return false;
		}

		game_objects.insert(std::pair<std::string, std::shared_ptr<GameObject>>(name, new_game_object));

		return true;
	}


	std::shared_ptr<GameObject> Scene::GetGameObject(std::string name)
	{
		auto result = game_objects.find(name);

		if (result == game_objects.end())
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

		for (auto& it : game_objects)
		{
			result.push_back(it.second);
		}

		return result;
	}
}