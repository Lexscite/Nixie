#include "vector.h"

namespace Nixie
{
	Vector2::Vector2() : x(0), y(0) {}
	Vector2::Vector2(float value) : x(value), y(value) {}
	Vector2::Vector2(float x, float y) : x(x), y(y) {}

	inline float Vector2::GetMagnitude()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 Vector2::Normalize()
	{
		float m = GetMagnitude();
		return m == 1 || m == 0 ? *this : Vector2(x / m, y / m);
	}

	Vector3::Vector3() : x(0), y(0), z(0) {}
	Vector3::Vector3(float value) : x(value), y(value), z(value) {}
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	inline float Vector3::GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Vector3::Normalize()
	{
		float m = GetMagnitude();
		return m == 1 || m == 0 ? *this : Vector3(x / m, y / m, z / m);
	}

	Vector3 Vector3::Rotate(Quaternion q)
	{
		Vector3 qv = Vector3(q.x, q.y, q.z);
		float qs = q.w;
		Vector3 result = 2.0f * Dot(qv, *this) * qv + (qs * qs - Dot(qv, qv)) * *this + 2.0f * qs * Cross(qv, *this);

		x = result.x;
		y = result.y;
		z = result.z;

		return *this;
	}

	inline float Vector3::Dot(Vector3 v1, Vector3 v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
	{
		return Vector3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}
}