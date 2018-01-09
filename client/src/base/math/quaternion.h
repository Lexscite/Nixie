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
		float x =  this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y + this->w * quaternion.x;
		float y = -this->x * quaternion.z + this->y * quaternion.w + this->z * quaternion.x + this->w * quaternion.y;
		float z =  this->x * quaternion.y - this->y * quaternion.x + this->z * quaternion.w + this->w * quaternion.z;
		float w = -this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z + this->w * quaternion.w;

		return Quaternion(x, y, z, w);
	}

	inline Quaternion Quaternion::operator*(float scalar)
	{
		return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	inline Quaternion& Quaternion::operator*=(const Quaternion& quaternion)
	{
		float x =  this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y + this->w * quaternion.x;
		float y = -this->x * quaternion.z + this->y * quaternion.w + this->z * quaternion.x + this->w * quaternion.y;
		float z =  this->x * quaternion.y - this->y * quaternion.x + this->z * quaternion.w + this->w * quaternion.z;
		float w = -this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z + this->w * quaternion.w;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}
}

#endif