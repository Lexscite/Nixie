#ifndef NIXIE_VECTOR4_H_
#define NIXIE_VECTOR4_H_

#pragma once

#include "math.h"


namespace Nixie
{
	template<class T>
	class Vector4
	{
	public:
		Vector4() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0)) {}
		Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Vector4(T* a) : x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}

		inline T GetMagnitude() { return sqrt<T>(x * x + y * y + z * z + w * w); }
		inline Vector4<T>& Normalize() { return static_cast<T>(1) / GetMagnitude(); }
		inline void Inverse() { x = -x; y = -y; z = -z; w = -w; }

	public:
		T x, y, z, w;
	};
}

#endif