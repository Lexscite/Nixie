#ifndef vodoo_COLOR_H_
#define vodoo_COLOR_H_

#pragma once

#include "math.h"
#include "vector.h"


namespace vodoo
{
	class Color
	{
	public:
		Color() {};
		Color(const float& s) { float cs = ClampChannel(s); r = g = b = cs; }
		Color(const float& r, const float& g, const float& b) : r(ClampChannel(r)), g(ClampChannel(g)), b(ClampChannel(b)), a(1) {}
		Color(const float& r, const float& g, const float& b, const float& a) : r(ClampChannel(r)), g(ClampChannel(g)), b(ClampChannel(b)), a(ClampChannel(a)) {}
		Color(const Vector3<float>& v) : r(ClampChannel(v.x)), g(ClampChannel(v.y)), b(ClampChannel(v.z)), a(1) {}
		Color(const Vector3<float>& v, float a) : r(ClampChannel(v.x)), g(ClampChannel(v.y)), b(ClampChannel(v.z)), a(ClampChannel(a)) {}

		inline operator float*() const { return new float[4]{ r, g, b, a }; };

	private:
		float ClampChannel(float value) { return Clamp<float>(value, 0.0f, 255.0f) / 255.0f; }

	public:
		float r, g, b, a;
	};
}

#endif