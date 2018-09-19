#include "../../stdafx.h"

#include "scene.h"
#include "components/model.h"
#include "components/text.h"


namespace nixie
{
	Scene::Scene() :
		clear_color_(Color(100, 100, 100))
	{}


	bool Scene::Init()
	{
		auto camera = std::make_shared<GameObject>("Camera");
		camera->AddComponent(std::make_shared<Camera>());
		camera->GetTransform()->SetPosition(0, 0, 10);
		AddGameObject(camera);

		//auto deer = std::make_shared<GameObject>("Deer");
		//deer->AddComponent(std::make_shared<Model>(
		//	"../data/meshes/deer.txt",
		//	"../data/shaders/default_vs.cso",
		//	"../data/shaders/default_ps.cso",
		//	"../data/textures/mailbox.jpg"));
		//AddGameObject(deer);

		//auto text = std::make_shared<GameObject>("Text");
		//text->AddComponent(std::make_shared<Text>(
		//	"Hello",
		//	"../data/shaders/font_vs.cso",
		//	"../data/shaders/font_ps.cso",
		//	"../data/textures/fonts/consolas.png"));
		//text->GetTransform()->SetScale(.1f);
		//AddGameObject(text);

		auto tri = std::make_shared<GameObject>("Tri");
		tri->AddComponent(std::make_shared<Model>(
			"../data/meshes/tri.txt",
			"../data/shaders/default_vs.cso",
			"../data/shaders/default_ps.cso",
			"../data/textures/mailbox.jpg"));
		tri->GetTransform()->SetPosition(-1, 0, 0);
		AddGameObject(tri);

		auto quat = std::make_shared<GameObject>("Quat");
		quat->AddComponent(std::make_shared<Model>(
			"../data/meshes/quat.txt",
			"../data/shaders/default_vs.cso",
			"../data/shaders/default_ps.cso",
			"../data/textures/mailbox.jpg"));
		quat->GetTransform()->SetPosition(1, 0, 0);
		AddGameObject(quat);

		SetCamera(std::static_pointer_cast<Camera>(camera->GetComponent("Camera")));

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
		camera_->CalculateViewMatrix();

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