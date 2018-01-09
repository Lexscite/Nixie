#include "quaternion.h"

namespace Nixie
{
	Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}

	Quaternion::Quaternion(float value) : x(value), y(value), z(value), w(value) {}

	Quaternion::Quaternion(float x, float y, float z) : x(x), y(y), z(z), w(1) {}

	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Quaternion::Quaternion(Vector3 vector) : x(vector.x), y(vector.y), z(vector.z), w(1) {}

	Quaternion::Quaternion(Vector3 vector, float w) : x(vector.x), y(vector.y), z(vector.z), w(w) {}

	inline float Quaternion::GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::Normalize()
	{
		Quaternion quaternion;
		float magnitude = GetMagnitude();

		if (magnitude != 0)
			quaternion = Quaternion(
				this->x / magnitude,
				this->y / magnitude,
				this->z / magnitude,
				this->w / magnitude);

		return quaternion;
	}
}