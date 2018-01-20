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

		float GetMagnitude();
		Quaternion Normalize();

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator*(float s) const;
		Quaternion& operator*=(const Quaternion& q);

	private:
		Quaternion & Set(float roll, float pitch, float yaw);

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

	inline Quaternion& Quaternion::Set(float roll, float pitch, float yaw)
	{
		float angle;

		angle = roll * 0.5f;
		const float roll_sin = sinf(angle);
		const float roll_cos = cosf(angle);

		angle = pitch * 0.5f;
		const float pitch_sin = sinf(angle);
		const float pitch_cos = cosf(angle);

		angle = yaw * 0.5f;
		const float yaw_sin = sinf(angle);
		const float yaw_cos = cosf(angle);

		const float	pitch_cos_yaw_cos = pitch_cos * yaw_cos;
		const float pitch_sin_yaw_cos = pitch_sin * yaw_cos;
		const float pitch_cos_yaw_sin = pitch_cos * yaw_sin;
		const float pitch_sin_yaw_sin = pitch_sin * yaw_sin;

		x = roll_sin * pitch_cos_yaw_cos - roll_cos * pitch_sin_yaw_sin;
		y = roll_cos * pitch_sin_yaw_cos + roll_sin * pitch_cos_yaw_sin;
		z = roll_cos * pitch_cos_yaw_sin - roll_sin * pitch_sin_yaw_cos;
		w = roll_cos * pitch_cos_yaw_cos + roll_sin * pitch_sin_yaw_sin;

		return Normalize();
	}
}

#endif