#ifndef NIXIE_TEXT_H_
#define NIXIE_TEXT_H_

#pragma once

#include "../component.h"
#include "../../graphics/font.h"
#include "../../graphics/mesh.h"
#include "../../graphics/material.h"


namespace nixie
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

		std::shared_ptr<Font> font_;
		std::shared_ptr<Mesh> mesh_;
		std::shared_ptr<Material> material_;
	};
}

#endif