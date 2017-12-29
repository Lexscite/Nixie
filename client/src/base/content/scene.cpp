#include "scene.h"

Scene::Scene() = default;

bool Scene::Init()
{
	clear_color_ = new Color(0, 100, 150);

	GameObject* test_camera_object = new GameObject("Camera");
	test_camera_object->SetPosition(new Vector3(6, 8, -6));
	test_camera_object->SetRotation(new Vector3(45, -45, 0));
	test_camera_object->AddComponent(new Camera);
	current_camera_ = static_cast<Camera*>(test_camera_object->GetComponent("Camera"));
	AddGameObject(test_camera_object);

	GameObject* test_game_object = new GameObject("Cube");
	test_game_object->AddComponent(new Mesh("../data/meshes/cube.txt"));
	test_game_object->AddComponent(new Material);
	test_game_object->SetPosition(new Vector3(1.5, 0, 1.5));
	AddGameObject(test_game_object);

	GameObject* test_game_object2 = new GameObject("Cube2");
	test_game_object2->AddComponent(new Mesh("../data/meshes/cube.txt"));
	test_game_object2->AddComponent(new Material);
	test_game_object2->SetPosition(new Vector3(-1.5, 0, 1.5));
	AddGameObject(test_game_object2);

	GameObject* test_game_object3 = new GameObject("Cube3");
	test_game_object3->AddComponent(new Mesh("../data/meshes/cube.txt"));
	test_game_object3->AddComponent(new Material);
	test_game_object3->SetPosition(new Vector3(-1.5, 0, -1.5));
	AddGameObject(test_game_object3);

	GameObject* test_game_object4 = new GameObject("Cube4");
	test_game_object4->AddComponent(new Mesh("../data/meshes/cube.txt"));
	test_game_object4->AddComponent(new Material);
	test_game_object4->SetPosition(new Vector3(1.5, 0, -1.5));
	AddGameObject(test_game_object4);

	for each (GameObject* game_object in GetGameObjects())
		if (!game_object->Init())
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

Color* Scene::GetClearColor()
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
	std::cout << "GameObjects count: " << game_objects_.size() << std::endl;
	if (game_objects_.size() == 0)
		return;

	for each (GameObject* game_object in GetGameObjects())
	{
		std::cout << std::endl << "GameObject: " << game_object->GetName() << std::endl;
		std::cout << "\tPosition: " << game_object->GetPosition()->x << ", " << game_object->GetPosition()->y << ", " << game_object->GetPosition()->z << std::endl;
		std::cout << "\tRotation: " << game_object->GetRotation()->x << ", " << game_object->GetRotation()->y << ", " << game_object->GetRotation()->z << std::endl;
		std::cout << "\tScale: " << game_object->GetScale()->x << ", " << game_object->GetScale()->y << ", " << game_object->GetScale()->z << std::endl;
		std::cout << "\tComponents:" << std::endl;

		for each (Component* component in game_object->GetComponents())
			std::cout << "\t\t" << component->GetName() << std::endl;
	}
}