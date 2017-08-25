#ifndef __COLOR_H__
#define __COLOR_H__

#pragma once

#include "Vector.h"

struct Color
{
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(IntVector3 vector);
	Color(Vector3 vector);

	float r, g, b, a;
};

#endif