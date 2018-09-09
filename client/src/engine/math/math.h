#ifndef NIXIE_MATH_H_
#define NIXIE_MATH_H_

#pragma once

#include <algorithm>


namespace Nixie
{
	class Vector2;
	class Vector3;
	class Quaternion;
	class Color;

	template<class T>
	T Clamp(T v, T l, T h)
	{
		return std::max(l, std::min(v, h));
	}
}

#endif