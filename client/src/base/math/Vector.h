#ifndef __VECTOR_H__
#define __VECTOR_H__

#pragma once

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float x;
	float y;
};

struct Vector3
{
	Vector3();
	Vector3(float x, float y, float z);

	float x;
	float y;
	float z;
};

struct Vector4
{
	Vector4();
	Vector4(float x, float y, float z, float t);

	float x;
	float y;
	float z;
	float t;
};

struct IntVector2
{
	IntVector2();
	IntVector2(int x, int y);

	int x;
	int y;
};

struct IntVector3
{
	IntVector3();
	IntVector3(int x, int y, int z);

	int x;
	int y;
	int z;
};

struct IntVector4
{
	IntVector4();
	IntVector4(int x, int y, int z, int t);

	int x;
	int y;
	int z;
	int t;
};

#endif