#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include "math.h"

namespace Nixie
{
	class Quaternion;

	class Vector2
	{
	public:
		Vector2();
		Vector2(float value);
		Vector2(float x, float y);

		float GetMagnitude();
		Vector2 Normalize();

	public:
		float x, y;
	};

	class Vector3
	{
	public:
		Vector3();
		Vector3(float value);
		Vector3(float x, float y, float z);
		
		static Vector3 Up() { return Vector3(0, 1, 0); }
		static Vector3 Down() { return Vector3(0, -1, 0); }
		static Vector3 Right() { return Vector3(1, 0, 0); }
		static Vector3 Left() { return Vector3(-1, 1, 0); }
		static Vector3 Forward() { return Vector3(0, 0, -1); }
		static Vector3 Backward() { return Vector3(0, 0, 1); }

		float GetMagnitude();
		Vector3 Normalize();
		Vector3 Rotate(Quaternion q);

		static float Dot(Vector3 v1, Vector3 v2);
		static Vector3 Cross(Vector3 v1, Vector3 v2);

		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator-() const;
		Vector3 operator*(float s) const;
		Vector3 operator/(float s) const;

		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);

	public:
		float x, y, z;
	};

	inline Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline Vector3 Vector3::operator*(float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	inline Vector3 operator*(float s, const Vector3& v)
	{
		return Vector3(v.x * s, v.y * s, v.z * s);
	}

	inline Vector3 Vector3::operator/(float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	inline Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}
}

#endif