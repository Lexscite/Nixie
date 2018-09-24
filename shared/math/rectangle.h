#ifndef NIXIE_RECTANGLE_H_
#define NIXIE_RECTANGLE_H_

#include "vector.h"

namespace nixie
{
	class Rectangle
	{
	public:
		Rectangle() : Rectangle(0, 0) {}
		Rectangle(float s) : Rectangle(s, s) {}
		Rectangle(float width, float height) : width(width), height(height) {}

		Vector2f GetCenter()
		{
			return Vector2f(width / 2, height / 2);
		}

	public:
		float width, height;
	};
}

#endif