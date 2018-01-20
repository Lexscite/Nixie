#include "scene.h"

namespace Nixie
{
	Scene::Scene() = default;

	bool Scene::Init()
	{
		clear_color_ = Color(100.0f, 100.0f, 100.0f);

		GameObject* camera = new GameObject("Camera");
		camera->AddComponent(new Camera);
		camera->GetTransform()->SetPosition(0, 10.0f, -6.0f);
		camera->GetTransform()->SetRotation(1.0f, 0, 0);
		current_camera_ = static_cast<Camera*>(camera->GetComponent("Camera"));
		AddGameObject(camera);

		GameObject* terrain = new GameObject("Terrain");
		terrain->AddComponent(new Terrain);
		terrain->AddComponent(new Material);
		AddGameObject(terrain);

		GameObject* cube = new GameObject("Cube");
		cube->AddComponent(new Mesh("../data/meshes/cube.txt"));
		cube->AddComponent(new Material);
		cube->GetTransform()->SetPosition(0, 0.5f, 5.0f);
		AddGameObject(cube);

		GameObject* player = new GameObject("Player");
		player->AddComponent(new Mesh("../data/meshes/cube.txt"));
		player->AddComponent(new Material);
		player->AddComponent(new Movement);
		player->GetTransform()->SetPosition(0, 0.5f, 0);
		AddGameObject(player);

		for each (GameObject* game_object in GetGameObjects())
			if (!game_object->Init(this))
				return false;

#ifdef _DEBUG
		OutputDebugMessage();
#endif

		return true;
	}

	void Scene::Release()
	{
		for each (GameObject* game_object in GetGameObjects())
			safe_release(game_object);
	}

	void Scene::Update()
	{
		current_camera_->Render();

		for each (GameObject* game_object in GetGameObjects())
			game_object->Update();
	}

	Color Scene::GetClearColor()
	{
		return clear_color_;
	}

	Camera* Scene::GetCamera()
	{
		return current_camera_;
	}

	bool Scene::AddGameObject(GameObject* new_game_object)
	{
		std::string name = new_game_object->GetName();

		if (GetGameObject(name) != nullptr)
			return false;

		game_objects_.insert(std::pair<std::string, GameObject*>(name, new_game_object));
		return true;
	}

	GameObject* Scene::GetGameObject(std::string name)
	{
		std::map<std::string, GameObject*>::iterator result = game_objects_.find(name);
		if (result == game_objects_.end())
			return nullptr;
		else
			return result->second;
	}

	std::vector<GameObject*> Scene::GetGameObjects()
	{
		std::vector<GameObject*> result;

		for (std::map<std::string, GameObject*>::iterator it = game_objects_.begin(); it != game_objects_.end(); ++it)
			result.push_back(it->second);

		return result;
	}

	void Scene::OutputDebugMessage()
	{
		std::cout << "Scene info:" << std::endl << std::endl << "GameObjects count: " << game_objects_.size() << std::endl;

		for each (GameObject* game_object in GetGameObjects())
		{
			std::cout << std::endl << "GameObject: " << game_object->GetName() << std::endl;

			Vector3 position = game_object->GetTransform()->GetPosition();
			std::cout << "\tPosition: " << position.x << ", " << position.y << ", " << position.z << std::endl;
			Quaternion rotation = game_object->GetTransform()->GetRotation();
			std::cout << "\tRotation: " << rotation.x << ", " << rotation.y << ", " << rotation.z << std::endl;
			Vector3 scale = game_object->GetTransform()->GetScale();
			std::cout << "\tScale: " << scale.x << ", " << scale.y << ", " << scale.z << std::endl;

			std::cout << "\tComponents:" << std::endl;
			for each (Component* component in game_object->GetComponents())
				std::cout << "\t\t" << component->GetName() << std::endl;
		}

		std::cout << std::endl;
	}
}