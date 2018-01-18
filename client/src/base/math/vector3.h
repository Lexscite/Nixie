#ifndef VECTOR3_H
#define VECTOR3_H

#pragma once

#include <math.h>

namespace Nixie
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float value);
		Vector3(float x, float y, float z);

		float GetMagnitude();
		Vector3 Normalize();

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