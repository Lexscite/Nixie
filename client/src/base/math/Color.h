#ifndef __COLOR_H__
#define __COLOR_H__

#pragma once

#include "math.h"
#include "vector.h"

class Color
{
public:
	Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}

	Color(int r, int g, int b)
	{
		this->r = ClampValue(r);
		this->g = ClampValue(g);
		this->b = ClampValue(b);
		a = 1.0f;
	}

	Color(int r, int g, int b, int a)
	{
		this->r = ClampValue(r);
		this->g = ClampValue(g);
		this->b = ClampValue(b);
		this->a = ClampValue(a);
	}

	Color(Vector3 vector)
	{
		this->r = ClampValue(vector.x);
		this->g = ClampValue(vector.y);
		this->b = ClampValue(vector.z);
		a = 1.0f;
	}

	Color(Vector4 vector)
	{
		this->r = ClampValue(vector.x);
		this->g = ClampValue(vector.y);
		this->b = ClampValue(vector.z);
		this->a = ClampValue(vector.t);
	}

	Color(IntVector3 vector)
	{
		this->r = ClampValue(vector.x);
		this->g = ClampValue(vector.y);
		this->b = ClampValue(vector.z);
		a = 1.0f;
	}

	Color(IntVector4 vector)
	{
		this->r = ClampValue(vector.x);
		this->g = ClampValue(vector.y);
		this->b = ClampValue(vector.z);
		this->a = ClampValue(vector.t);
	}

private:
	float ClampValue(int value)
	{
		return clamp((float)value, 0.0f, 255.0f) / 255;
	}

	float ClampValue(float value)
	{
		return clamp(value, 0.0f, 255.0f) / 255;
	}

public:
	float r, g, b, a;
};

#endif