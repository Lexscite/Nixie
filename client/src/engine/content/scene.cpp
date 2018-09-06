#include "../../stdafx.h"

#include "scene.h"
#include "components/model.h"


namespace Nixie
{
	Scene::Scene() :
		clear_color(Color())
	{}


	bool Scene::Init()
	{
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>("Camera");
		camera->AddComponent(std::make_shared<Camera>());
		camera->GetTransform()->SetPosition(-2, 1.3f, -1.5f);
		camera->GetTransform()->SetRotation(0.3f, 1, 0);
		current_camera = std::static_pointer_cast<Camera>(camera->GetComponent("Camera"));
		AddGameObject(camera);

		std::shared_ptr<GameObject> mailbox = std::make_shared<GameObject>("Mailbox");
		mailbox->AddComponent(std::make_shared<Model>("../data/meshes/mailbox.txt", "../data/shaders/default_vs.cso", "../data/shaders/default_ps.cso", "../data/textures/mailbox.jpg"));
		AddGameObject(mailbox);

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