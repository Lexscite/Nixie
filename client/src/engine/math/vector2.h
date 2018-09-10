#ifndef NIXIE_VECTOR2_H_
#define NIXIE_VECTOR2_H_

#pragma once

#include "math.h"


namespace Nixie
{
	template<class T>
	class Vector2
	{
	public:
		Vector2() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
		Vector2(T x, T y) : x(x), y(y) {}
		Vector2(T* a) : x(a[0]), y(a[1]) {}

		inline T GetMagnitude() { return sqrt<T>(x * x + y * y); }
		inline Vector2<T> Normalize() { return static_cast<T>(1) / GetMagnitude(); }
		inline void Inverse() { x = -x; y = -y; }

	public:
		T x, y;
	};
}

#endif