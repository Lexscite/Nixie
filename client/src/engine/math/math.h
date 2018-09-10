#ifndef NIXIE_MATH_H_
#define NIXIE_MATH_H_

#pragma once

#include <algorithm>


namespace Nixie
{
	template<class T>
	class Vector2;

	template<class T>
	class Vector3;

	template<class T>
	class Vector4;

	class Quaternion;

	class Matrix;

	class Color;

	template<class T>
	T Clamp(T v, T l, T h)
	{
		return std::max(l, std::min(v, h));
	}
}

#endif