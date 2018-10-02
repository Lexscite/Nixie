#ifndef vodoo_MODEL_H_
#define vodoo_MODEL_H_

#pragma once

#include "core/component.h"
#include "core/graphics/mesh.h"
#include "core/graphics/material.h"


namespace vodoo
{
	class Model : public Component
	{
	public:
		Model(std::string mesh_file_path, std::string vs_shader_path, std::string ps_shader_path, std::string texture_path);

	private:
		virtual bool OnInit() override;
		virtual bool OnUpdate() override;

	private:
		std::string mesh_path_;
		std::string vs_path_;
		std::string ps_path_;
		std::string texture_path_;

		std::shared_ptr<Mesh> mesh_;
		std::shared_ptr<Material> material_;
	};
}

#endif