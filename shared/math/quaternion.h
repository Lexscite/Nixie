#ifndef NIXIE_QUATERNION_H_
#define NIXIE_QUATERNION_H_

#include "mathfu/quaternion.h"


namespace nixie
{
	template<class T>
	using Quaternion = mathfu::Quaternion<T>;

	using Quaternionf = mathfu::Quaternion<float>;
}

#endif