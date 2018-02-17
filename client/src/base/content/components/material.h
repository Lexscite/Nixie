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
		Material(const wchar_t* texture_path);

		Shader* GetShader();

	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

		bool LoadTexture();

	private:
		const wchar_t* texture_path;

		Shader* shader;
		Texture* texture;
	};
}

#endif