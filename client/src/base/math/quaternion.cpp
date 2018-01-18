#include "quaternion.h"

namespace Nixie
{
	Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
	Quaternion::Quaternion(float value) : x(value), y(value), z(value), w(value) {}
	Quaternion::Quaternion(float x, float y, float z) : x(x), y(y), z(z), w(1) {}
	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Quaternion::Quaternion(Vector3 v) : x(v.x), y(v.y), z(v.z), w(1) {}
	Quaternion::Quaternion(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

	inline float Quaternion::GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::Normalize()
	{
		float m = GetMagnitude();
		return m == 1 || m == 0 ? *this : Quaternion(x / m, y / m, z / m, w / m);
	}
}