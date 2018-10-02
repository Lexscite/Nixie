#ifndef vodoo_FONT_H_
#define vodoo_FONT_H_

#pragma once

#include "texture.h"
#include "mesh.h"
#include "math/vector.h"


namespace vodoo
{
	class Font
	{
	public:
		struct CharData
		{
			float x, y, width, height, origin_x, origin_y;
		};

	public:
		Font();

		bool Init();

		float GetWidth();
		float GetHeight();
		CharData GetCharData(const char& c);

	private:
		float width_, height_;

		std::map<char, Font::CharData> characters_;
	};
}

#endif