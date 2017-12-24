#include "Scene.h"

Scene::Scene() = default;

bool Scene::Init()
{
	clear_color_ = new Color(0, 100, 200);

	camera_ = new Camera;
	if (!camera_)
		return false;

	camera_->position_ = new Vector3(0.0f, 0.0f, -5.0f);

	GameObject* testGameObject = new GameObject;
	game_objects_.push_back(testGameObject);

	for each (GameObject* gameObject in game_objects_)
		if (!gameObject->Init())
			return false;

	std::cout << "GameObjects count: " << game_objects_.size() << std::endl;
	if (game_objects_.size() > 0)
		for (int i = 0; i < static_cast<int>(game_objects_.size()); i++)
		{
			GameObject* game_object = game_objects_[i];
			std::cout << std::endl << "GameObject #" << i << std::endl;
			std::cout << "	pos: " << game_object->position_->x << ", " << game_object->position_->y << ", " << game_object->position_->z << std::endl;
		}

	return true;
}

void Scene::Release()
{
	for each (GameObject* game_object in game_objects_)
		safe_delete(game_object);
}

void Scene::Update()
{
	for each (GameObject* game_object in game_objects_)
		game_object->Update();
}

Color* Scene::GetClearColor()
{
	return clear_color_;
}

Camera* Scene::GetCamera()
{
	return camera_;
}

std::vector<GameObject*> Scene::GetGameObjects()
{
	return game_objects_;
}