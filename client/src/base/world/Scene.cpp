#include "Scene.h"

bool Scene::Init()
{
	clear_color_ = new Color(0, 100, 200);

	GameObject* testGameObject = new GameObject;

	game_objects_.push_back(testGameObject);

	for each (GameObject* gameObject in game_objects_)
	{
		if (!gameObject->Init())
			return false;
	}

	std::cout << "GameObjects count: " << game_objects_.size() << std::endl;
	if (game_objects_.size() > 0)
	{
		for (int i = 0; i < static_cast<int>(game_objects_.size()); i++)
		{
			GameObject* game_object = game_objects_[i];
			std::cout << std::endl << "GameObject #" << i << std::endl;
			std::cout << "	pos: " << game_object->m_position->x << ", " << game_object->m_position->y << ", " << game_object->m_position->z << std::endl;
		}
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