#ifndef NIXIE_RECTANGLE_H_
#define NIXIE_RECTANGLE_H_

#pragma once

#include "vector.h"


namespace nixie
{
	template<class T>
	class Rectangle
	{
	public:
		Rectangle() : Rectangle(T(0), T(0)) {}
		Rectangle(T s) : Rectangle(s, s) {}
		Rectangle(T width, T height) : width(width), height(height) {}

		Vector2<T> GetCenter()
		{
			return Vector2<T>(width / 2, height / 2);
		}

	public:
		T width, height;
	};

	using Rectanglef = Rectangle<float>;
}

#endif