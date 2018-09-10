#include "../../stdafx.h"

#include "vector3.h"
#include "quaternion.h"


namespace Nixie
{
	template<class T>
	Vector3<T> Vector3<T>::Rotate(const Quaternion& q)
	{
		Vector3 qv = Vector3(q.x, q.y, q.z);
		float qs = q.w;
		Vector3 result = 2.0f * Dot(qv, *this) * qv + (qs * qs - Dot(qv, qv)) * *this + 2.0f * qs * Cross(qv, *this);

		x = result.x;
		y = result.y;
		z = result.z;

		return *this;
	}
}