#ifndef VOODOO_TEXT_H_
#define VOODOO_TEXT_H_

#include "voodoo/component.h"
#include "voodoo/text_mesh.h"
#include "voodoo/material.h"

namespace voodoo
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