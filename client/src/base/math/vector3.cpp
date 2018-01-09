#include "vector3.h"

namespace Nixie
{
	Vector3::Vector3() : x(0), y(0), z(0) {}

	Vector3::Vector3(float value) : x(value), y(value), z(value) {}

	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	inline float Vector3::GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Vector3::Normalize()
	{
		Vector3 vector;
		float magnitude = GetMagnitude();

		if (magnitude == 1)
			return *this;
		else if (magnitude != 0)
			vector = Vector3(
				x / magnitude,
				y / magnitude,
				z / magnitude);

		return vector;
	}
}