#include "../../stdafx.h"

#include "quaternion.h"
#include "vector.h"


namespace Nixie
{
	Quaternion::Quaternion() : x(0), y(0), z(0), w(1.0f) {}
	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Quaternion::Quaternion(float r, float p, float y) { Set(r, p, y); }
	Quaternion::Quaternion(Vector3 v) { Set(v.x, v.y, v.z); }

	inline float Quaternion::GetMagnitude() { return sqrtf(x * x + y * y + z * z + w * w); }

	inline Quaternion& Quaternion::Normalize() { return (*this *= 1.0f / std::sqrtf(x * x + y * y + z * z + w * w)); }

	inline Quaternion& Quaternion::Set(float r, float p, float y)
	{
		float angle;

		angle = r * 0.5f;
		const float r_sin = sinf(angle);
		const float r_cos = cosf(angle);

		angle = p * 0.5f;
		const float p_sin = sinf(angle);
		const float p_cos = cosf(angle);

		angle = y * 0.5f;
		const float y_sin = sinf(angle);
		const float y_cos = cosf(angle);

		const float	p_cos_y_cos = p_cos * y_cos;
		const float p_sin_y_cos = p_sin * y_cos;
		const float p_cos_y_sin = p_cos * y_sin;
		const float p_sin_y_sin = p_sin * y_sin;

		this->x = r_sin * p_cos_y_cos - r_cos * p_sin_y_sin;
		this->y = r_cos * p_sin_y_cos + r_sin * p_cos_y_sin;
		this->z = r_cos * p_cos_y_sin - r_sin * p_sin_y_cos;
		this->w = r_cos * p_cos_y_cos + r_sin * p_sin_y_sin;

		return Normalize();
	}
}