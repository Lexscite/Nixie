#include "voodoo/component.h"

namespace voodoo
{
	bool Component::Init(std::shared_ptr<GameObject> game_object)
	{
		game_object_ = game_object;

		if (!OnInit()) {
			return false;
		}

		return true;
	}

	bool Component::OnInit()
	{
		return true;
	}

	bool Component::Update()
	{
		if (!OnUpdate()) {
			return false;
		}

		return true;
	}

	bool Component::OnUpdate()
	{
		return true;
	}

	std::string Component::GetName()
	{
		// TODO: Very strange stuff going on here so get it the hell out
		return std::string(typeid(*shared_from_this()).name()).erase(0, 14);
	}

	std::shared_ptr<Scene> Component::GetScene()
	{
		return game_object_->GetScene();
	}

	std::shared_ptr<GameObject> Component::GetGameObject()
	{
		return game_object_;
	}

	std::shared_ptr<Transform> Component::GetTransform()
	{
		return game_object_->GetTransform();
	}
}