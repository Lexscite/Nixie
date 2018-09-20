#ifndef NIXIE_FONT_H_
#define NIXIE_FONT_H_

#pragma once

#include "texture.h"
#include "mesh.h"
#include "math/vector.h"


namespace nixie
{
	class Font
	{
	public:
		struct CharData
		{
			int x, y, width, height, origin_x, origin_y;
		};

	public:
		Font();

		bool Init(std::string texture_path);

		std::vector<VertexPTN> BuildVertexArray(std::string s);
		
	private:
		bool LoadTexture(std::string texture_path);
		
		std::vector<VertexPTN> CreateCharPlane(const CharData& c, const Vector3<float>& pos);

	private:
		std::string name_;
		std::map<char, Font::CharData> characters_;

		int width_, height_;

		std::unique_ptr<Texture> texture_;
	};
}

#endif