#ifndef __VECTOR_H__
#define __VECTOR_H__

#pragma once

class Vector2
{
public:
	float x, y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float GetMagnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
};

class Vector3 : public Vector2
{
public:
	float z;

	Vector3() : Vector2()
	{
		z = 0;
	}

	Vector3(float x, float y, float z) : Vector2(x, y)
	{
		this->z = z;
	}

	float GetMagnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	static Vector3* Sum(Vector3* left, Vector3* right)
	{
		return new Vector3(
			left->x + right->x,
			left->y + right->y,
			left->z + right->z
		);
	}
};

class Vector4 : public Vector3
{
public:
	float t;

	Vector4() : Vector3()
	{
		t = 0;
	}

	Vector4(float x, float y, float z, float t) : Vector3(x, y, z)
	{
		this->t = t;
	}
};

class IntVector2
{
public:
	int x, y;

	IntVector2()
	{
		x = 0;
		y = 0;
	}

	IntVector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class IntVector3: public IntVector2
{
public:
	int z;

	IntVector3() : IntVector2()
	{
		z = 0;
	}

	IntVector3(int x, int y, int z) : IntVector2(x, y)
	{
		this->z = z;
	}
};

class IntVector4 : public IntVector3
{
public:
	int t;

	IntVector4() : IntVector3()
	{
		t = 0;
	}

	IntVector4(int x, int y, int z, int t) : IntVector3(x, y, z)
	{
		this->t = t;
	}
};

#endif