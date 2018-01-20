#include "quaternion.h"

namespace Nixie
{
	Quaternion::Quaternion() : x(0), y(0), z(0), w(1.0f) {}
	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Quaternion::Quaternion(float roll, float pitch, float yaw)
	{
		Set(roll, pitch, yaw);
	}

	Quaternion::Quaternion(Vector3 v)
	{
		Set(v.x, v.y, v.z);
	}

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