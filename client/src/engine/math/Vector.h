#ifndef __VECTOR_H__
#define __VECTOR_H__

#pragma once

struct Vector2
{
	Vector2(float x, float y);
	static Vector2* Zero();

	float x;
	float y;
};

struct Vector3
{
	Vector3(float x, float y, float z);
	static Vector3* Zero();

	float x;
	float y;
	float z;
};
struct IntVector2
{
	IntVector2(int x, int y);
	static IntVector2* Zero();

	int x;
	int y;
};

struct IntVector3
{
	IntVector3(int x, int y, int z);
	static IntVector3* Zero();

	int x;
	int y;
	int z;
};

#endif