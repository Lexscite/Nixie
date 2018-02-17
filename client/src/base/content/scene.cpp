#include "scene.h"

namespace Nixie
{
	Scene::Scene() :
		clear_color(Color())
	{}

	bool Scene::Init()
	{
		//GameObject* terrain = new GameObject("Terrain");
		//terrain->AddComponent(new Terrain);
		//terrain->AddComponent(new Material(L"../data/textures/placeholder.jpg"));
		//terrain->GetTransform()->SetPosition(-50.0f, 0, -50.0f);
		//AddGameObject(terrain);

		GameObject* ground = new GameObject("Ground");
		ground->AddComponent(new Mesh("../data/meshes/test_level_00_ground.txt"));
		ground->AddComponent(new Material(L"../data/textures/grass.jpg"));
		AddGameObject(ground);

		GameObject* crates = new GameObject("Crates");
		crates->AddComponent(new Mesh("../data/meshes/test_level_00_crates.txt"));
		crates->AddComponent(new Material(L"../data/textures/crate.jpg"));
		AddGameObject(crates);

		GameObject* player = new GameObject("Player");
		player->AddComponent(new Mesh("../data/meshes/cube.txt"));
		player->AddComponent(new Material(L"../data/textures/placeholder.jpg"));
		player->AddComponent(new Movement);
		player->GetTransform()->SetPosition(0, 0.5f, 0);
		AddGameObject(player);

		GameObject* test_child = new GameObject("Test Child");
		test_child->AddComponent(new Mesh("../data/meshes/cube.txt"));
		test_child->AddComponent(new Material(L"../data/textures/placeholder.jpg"));
		test_child->GetTransform()->SetPosition(-2.0f, 0, 0);
		test_child->GetTransform()->SetParent(player->GetTransform());
		AddGameObject(test_child);

		GameObject* camera_handle = new GameObject("Camer Handle");
		camera_handle->GetTransform()->SetParent(player->GetTransform());

		GameObject* camera = new GameObject("Camera");
		camera->AddComponent(new Camera);
		camera->GetTransform()->SetPosition(0, 12.0f, -8.0f);
		camera->GetTransform()->SetRotation(1.0f, 0, 0);
		camera->GetTransform()->SetParent(player->GetTransform());
		current_camera = static_cast<Camera*>(camera->GetComponent("Camera"));
		AddGameObject(camera);

		for each (GameObject* game_object in GetGameObjects())
			if (!game_object->Init(this))
				return false;

		return true;
	}

	void Scene::Release()
	{
		for each (GameObject* game_object in GetGameObjects())
			safe_release(game_object);
	}

	void Scene::Update()
	{
		current_camera->Render();

		for each (GameObject* game_object in GetGameObjects())
			game_object->Update();
	}

	Color Scene::GetClearColor()
	{
		return clear_color;
	}

	Camera* Scene::GetCamera()
	{
		return current_camera;
	}

	bool Scene::AddGameObject(GameObject* new_game_object)
	{
		std::string name = new_game_object->GetName();

		if (GetGameObject(name) != nullptr)
			return false;

		game_objects.insert(std::pair<std::string, GameObject*>(name, new_game_object));
		return true;
	}

	GameObject* Scene::GetGameObject(std::string name)
	{
		std::map<std::string, GameObject*>::iterator result = game_objects.find(name);
		if (result == game_objects.end())
			return nullptr;
		else
			return result->second;
	}

	std::vector<GameObject*> Scene::GetGameObjects()
	{
		std::vector<GameObject*> result;

		for (std::map<std::string, GameObject*>::iterator it = game_objects.begin(); it != game_objects.end(); ++it)
			result.push_back(it->second);

		return result;
	}
}