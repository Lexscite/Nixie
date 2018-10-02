#ifndef vodoo_MATH_H_
#define vodoo_MATH_H_

#include "mathfu/utilities.h"
#include "mathfu/constants.h"

namespace vodoo
{
	template<class T>
	const auto Clamp = mathfu::Clamp<T>;

	template<class T>
	inline T RadianToDegree(const T& r)
	{
		return (r * T(180)) / mathfu::kPi;
	}

	template<class T>
	inline T DegreeToRadian(const T& d)
	{
		return (d * mathfu::kPi) / 180;
	}
}

#endif