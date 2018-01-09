#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

#include "vector3.h"

namespace Nixie
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float value);
		Quaternion(float x, float y, float z);
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vector3 vector);
		Quaternion(Vector3 vector, float w);

		float GetMagnitude();
		Quaternion Normalize();

		Quaternion operator*(const Quaternion& quaternion);
		Quaternion operator*(float scalar);

		Quaternion& operator*=(const Quaternion& quaternion);

	public:
		float x, y, z, w;
	};

	inline Quaternion Quaternion::operator*(const Quaternion& quaternion)
	{
		float x = this->w * quaternion.x + this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y;
		float y = this->w * quaternion.y - this->x * quaternion.z + this->y * quaternion.w + this->z * quaternion.x;
		float z = this->w * quaternion.z + this->x * quaternion.y - this->y * quaternion.x + this->z * quaternion.w;
		float w = this->w * quaternion.w - this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z;

		return Quaternion(x, y, z, w);
	}

	inline Quaternion Quaternion::operator*(float scalar)
	{
		return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	inline Quaternion& Quaternion::operator*=(const Quaternion& right)
	{
		float x = this->w * right.x + this->x * right.w + this->y * right.z - this->z * right.y;
		float y = this->w * right.y - this->x * right.z + this->y * right.w + this->z * right.x;
		float z = this->w * right.z + this->x * right.y - this->y * right.x + this->z * right.w;
		float w = this->w * right.w - this->x * right.x - this->y * right.y - this->z * right.z;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}
}

#endif