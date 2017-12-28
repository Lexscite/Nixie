#include "scene.h"

Scene::Scene() = default;

bool Scene::Init()
{
	clear_color_ = new Color(0.5f, 0.5f, 0.5f);

	GameObject* test_camera_object = new GameObject("Camera");
	test_camera_object->SetPosition(new Vector3(5, 7, -5));
	test_camera_object->SetRotation(new Vector3(45, -45, 0));
	test_camera_object->AddComponent(new Camera);
	current_camera_ = static_cast<Camera*>(test_camera_object->GetComponent("Camera"));
	game_objects_.push_back(test_camera_object);

	GameObject* test_game_object = new GameObject("Cube");
	test_game_object->AddComponent(new Mesh("../data/meshes/cube.txt"));
	test_game_object->AddComponent(new Material);
	game_objects_.push_back(test_game_object);

	for each (GameObject* gameObject in game_objects_)
		if (!gameObject->Init())
			return false;

#ifdef _DEBUG
	OutputDebugMessage();
#endif

	return true;
}

void Scene::Release()
{
	for each (GameObject* game_object in game_objects_)
		safe_release(game_object);
}

void Scene::Update()
{
	current_camera_->Render();

	for each (GameObject* game_object in game_objects_)
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

std::vector<GameObject*> Scene::GetGameObjects()
{
	return game_objects_;
}

void Scene::OutputDebugMessage()
{
	std::cout << "GameObjects count: " << game_objects_.size() << std::endl;
	if (game_objects_.size() == 0)
		return;

	for each (GameObject* game_object in game_objects_)
	{
		std::cout << std::endl << "GameObject: " << game_object->name_ << std::endl;
		std::cout << "\tPosition: " << game_object->GetPosition()->x << ", " << game_object->GetPosition()->y << ", " << game_object->GetPosition()->z << std::endl;
		std::cout << "\tRotation: " << game_object->GetRotation()->x << ", " << game_object->GetRotation()->y << ", " << game_object->GetRotation()->z << std::endl;
		std::cout << "\tScale: " << game_object->GetScale()->x << ", " << game_object->GetScale()->y << ", " << game_object->GetScale()->z << std::endl;
		std::cout << "\tComponents:" << std::endl;

		for each (Component* component in game_object->GetComponents())
			std::cout << "\t\t" << component->GetName() << std::endl;
	}
}