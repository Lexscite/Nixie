#ifndef NIXIE_FONT_MESH_H_
#define NIXIE_FONT_MESH_H_

#pragma once

#include "mesh.h"
#include "font.h"


namespace nixie
{
	class TextMesh : public Mesh
	{
	public:
		TextMesh(std::shared_ptr<Font> font);

		void Generate(std::string text);

	private:
		std::vector<VertexPTN> GenerateChar(Font::CharData c, float offset);

	private:
		std::shared_ptr<Font> font_;
	};
}

#endif