#ifndef __COLOR_H__
#define __COLOR_H__

#pragma once

#include "math.h"
#include "vector.h"

struct Color
{
	float r, g, b, a;

	Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}

	Color(float r, float g, float b)
	{
		this->r = clamp(r, 0.0f, 1.0f);
		this->g = clamp(g, 0.0f, 1.0f);
		this->b = clamp(b, 0.0f, 1.0f);
		a = 1.0f;
	}

	Color(float r, float g, float b, float a)
	{
		this->r = clamp(r, 0.0f, 1.0f);
		this->g = clamp(g, 0.0f, 1.0f);
		this->b = clamp(b, 0.0f, 1.0f);
		this->a = clamp(a, 0.0f, 1.0f);
	}

	Color(Vector3 vector)
	{
		this->r = clamp(vector.x, 0.0f, 1.0f);
		this->g = clamp(vector.y, 0.0f, 1.0f);
		this->b = clamp(vector.z, 0.0f, 1.0f);
		a = 1.0f;
	}

	Color(Vector4 vector)
	{
		this->r = clamp(vector.x, 0.0f, 1.0f);
		this->g = clamp(vector.y, 0.0f, 1.0f);
		this->b = clamp(vector.z, 0.0f, 1.0f);
		this->a = clamp(vector.t, 0.0f, 1.0f);
	}
};

#endif