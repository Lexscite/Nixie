#ifndef vodoo_TEXT_H_
#define vodoo_TEXT_H_

#pragma once

#include "core/component.h"
#include "core/graphics/text_mesh.h"
#include "core/graphics/material.h"


namespace vodoo
{
	class Font;
	class Material;

	class Text : public Component
	{
	public:
		Text(std::string text, std::string vs_path, std::string ps_path, std::string texture_path);

		void SetText(const std::string& text) { text_ = text; }

	private:
		virtual bool OnInit() override;
		virtual bool OnUpdate() override;

	private:
		std::string text_;

		std::string vs_path_;
		std::string ps_path_;
		std::string texture_path_;

		std::shared_ptr<TextMesh> mesh_;
		std::shared_ptr<Material> material_;
	};
}

#endif