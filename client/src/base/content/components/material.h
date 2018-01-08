#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include "../component.h"
#include "../../graphics/texture.h"
#include "../../graphics/shader.h"

namespace Nixie
{
	class Material : public Component
	{
	public:
		Material();
		Shader* GetShader();

	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

		bool LoadTexture(const wchar_t* file_path);

	private:
		Shader * shader_;
		Texture* texture_;
	};
}

#endif