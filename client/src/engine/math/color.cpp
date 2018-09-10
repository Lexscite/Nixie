#include "../../stdafx.h"

#include "color.h"
#include "vector3.h"


namespace Nixie
{
	Color::Color() : r(0), g(0), b(0), a(1) {}


	Color::Color(float value)
	{
		value = ClampValue(value);
		r = value;
		g = value;
		b = value;
		a = 1.0f;
	}


	Color::Color(float r, float g, float b)
	{
		this->r = ClampValue(r);
		this->g = ClampValue(g);
		this->b = ClampValue(b);
		this->a = 1.0f;
	}


	Color::Color(float r, float g, float b, float a)
	{
		this->r = ClampValue(r);
		this->g = ClampValue(g);
		this->b = ClampValue(b);
		this->a = ClampValue(a);
	}


	Color::Color(const Vector3<float>& v)
	{
		r = ClampValue(v.x);
		g = ClampValue(v.y);
		b = ClampValue(v.z);
		a = 1.0f;
	}


	Color::Color(const Vector3<float>& v, float a)
	{
		this->r = ClampValue(v.x);
		this->g = ClampValue(v.y);
		this->b = ClampValue(v.z);
		this->a = ClampValue(a);
	}


	inline float Color::ClampValue(float value)
	{
		return Clamp<float>(value, 0.0f, 255.0f) / 255.0f;
	}
}