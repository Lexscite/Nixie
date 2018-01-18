#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

#include "vector3.h"

namespace Nixie
{
	class Vector3;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float value);
		Quaternion(float x, float y, float z);
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vector3 v);
		Quaternion(Vector3 v, float w);

		float GetMagnitude();
		Quaternion Normalize();

		Quaternion operator*(const Quaternion& q);
		Quaternion operator*(float s);

		Quaternion& operator*=(const Quaternion& quaternion);

	public:
		float x, y, z, w;
	};

	inline Quaternion Quaternion::operator*(const Quaternion& q)
	{
		float x =  this->x * q.w + this->y * q.z - this->z * q.y + this->w * q.x;
		float y = -this->x * q.z + this->y * q.w + this->z * q.x + this->w * q.y;
		float z =  this->x * q.y - this->y * q.x + this->z * q.w + this->w * q.z;
		float w = -this->x * q.x - this->y * q.y - this->z * q.z + this->w * q.w;

		return Quaternion(x, y, z, w);
	}

	inline Quaternion Quaternion::operator*(float scalar)
	{
		return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	inline Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		float x =  this->x * q.w + this->y * q.z - this->z * q.y + this->w * q.x;
		float y = -this->x * q.z + this->y * q.w + this->z * q.x + this->w * q.y;
		float z =  this->x * q.y - this->y * q.x + this->z * q.w + this->w * q.z;
		float w = -this->x * q.x - this->y * q.y - this->z * q.z + this->w * q.w;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}
}

#endif