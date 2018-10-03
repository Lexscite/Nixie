#ifndef VOODOO_FONT_H_
#define VOODOO_FONT_H_

#include "texture.h"
#include "mesh.h"
#include "vector.h"

#include <map>

namespace voodoo
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