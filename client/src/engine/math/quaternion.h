#ifndef NIXIE_QUATERNION_H_
#define NIXIE_QUATERNION_H_

#pragma once

#include "math.h"
#include "vector3.h"


namespace Nixie
{
	class Quaternion
	{
	public:
		Quaternion() : v(), w(0) {}
		Quaternion(float x, float y, float z, float w) : v(Vector3<float>(x, y, z)), w(w) {}
		Quaternion(const Vector3<float>& v, float w) : v(v), w(w) {}
		Quaternion(const Quaternion& q) : v(q.v), w(q.w) {}

		inline float GetMagnitude() { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + w * w); }
		inline Quaternion& Normalize() { return (*this *= 1.0f / GetMagnitude()); }

		inline Quaternion operator*(const Quaternion& q) const;
		inline Quaternion operator*(float s) const;
		inline Quaternion& operator*=(const Quaternion& q);
		inline Quaternion& operator*=(float s);

	public:
		Vector3<float> v;
		float w;
	};

	inline Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		return Quaternion(
			(q.w * v.x) + (q.v.x * w) + (q.v.y * v.z) - (q.v.z * v.y),
			(q.w * v.y) + (q.v.y * w) + (q.v.z * v.x) - (q.v.x * v.z),
			(q.w * v.z) + (q.v.z * w) + (q.v.x * v.y) - (q.v.y * v.x),
			(q.w * w) - (q.v.x * v.x) - (q.v.y * v.y) - (q.v.z * v.z));
	}

	inline Quaternion Quaternion::operator*(float s) const
	{
		return Quaternion(v.x * s, v.y * s, v.z * s, w * s);
	}

	inline Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		return (*this = q * (*this));
	}

	inline Quaternion & Quaternion::operator*=(float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		w *= s;

		return *this;
	}
}

#endif