#ifndef NIXIE_MODEL_H_
#define NIXIE_MODEL_H_

#pragma once

#include "../component.h"
#include "../../graphics/mesh.h"
#include "../../graphics/material.h"


namespace Nixie
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

		std::shared_ptr<Mesh<VertexPTN>> mesh_;
		std::shared_ptr<Material> material_;
	};
}

#endif