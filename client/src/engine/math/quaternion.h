#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

#include "math.h"

namespace Nixie
{
	class Vector3;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(float x, float y, float z);
		Quaternion(Vector3 v);

		inline float GetMagnitude();
		inline Quaternion& Normalize();

		inline Quaternion operator*(const Quaternion& q) const;
		inline Quaternion operator*(float s) const;
		inline Quaternion& operator*=(const Quaternion& q);
		inline Quaternion& operator*=(float s);

	private:
		inline Quaternion& Set(float r, float p, float y);

	public:
		float x, y, z, w;
	};

	inline Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		return Quaternion(
			(q.w * x) + (q.x * w) + (q.y * z) - (q.z * y),
			(q.w * y) + (q.y * w) + (q.z * x) - (q.x * z),
			(q.w * z) + (q.z * w) + (q.x * y) - (q.y * x),
			(q.w * w) - (q.x * x) - (q.y * y) - (q.z * z));
	}

	inline Quaternion Quaternion::operator*(float s) const
	{
		return Quaternion(x * s, y * s, z * s, w * s);
	}

	inline Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		return (*this = q * (*this));
	}

	inline Quaternion & Quaternion::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}
}

#endif