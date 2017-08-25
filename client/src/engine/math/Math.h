#ifndef __MATH_H__
#define __MATH_H__

#pragma once

int clamp(int number, int min, int max)
{
	if (number > max)
		number = max;

	if (number < min)
		number = min;
}

float clamp(float number, float min, float max)
{
	if (number > max)
		number = max;

	if (number < min)
		number = min;
}

#endif