#ifndef VOODOO_GAME_OBJECT_H_
#define VOODOO_GAME_OBJECT_H_

#pragma once


namespace voodoo
{
	class Scene;
	class Component;
	class Transform;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(std::string name);

		bool Init(std::shared_ptr<Scene> scene);
		bool Update();

		bool AddComponent(std::shared_ptr<Component> new_component);
		std::shared_ptr<Component> GetComponent(std::string name);
		std::vector<std::shared_ptr<Component>> GetComponents();

		std::string GetName() { return name_; }
		std::shared_ptr<Scene> GetScene() { return scene_; }
		std::shared_ptr<GameObject> GetParent() { return parent_; }
		std::shared_ptr<Transform> GetTransform() { return transform_; }

	private:
		std::string name_;
		std::shared_ptr<Scene> scene_;
		std::shared_ptr<GameObject> parent_;
		std::shared_ptr<Transform> transform_;
		std::map<std::string, std::shared_ptr<Component>> components_;
	};
}

#endif