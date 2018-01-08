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

		Vector3 operator+(const Vector3& vector) const;
		Vector3 operator-(const Vector3& vector) const;
		Vector3 operator-() const;
		Vector3 operator*(float scalar) const;
		Vector3 operator/(float scalar) const;

		Vector3& operator+=(const Vector3& vector);
		Vector3& operator-=(const Vector3& vector);

	public:
		float x, y, z;
	};

	inline Vector3 Vector3::operator+(const Vector3& vector) const
	{
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	}

	inline Vector3 Vector3::operator-(const Vector3& vector) const
	{
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	}

	inline Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	inline Vector3 Vector3::operator/(float scalar) const
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	inline Vector3& Vector3::operator+=(const Vector3& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}
}

#endif