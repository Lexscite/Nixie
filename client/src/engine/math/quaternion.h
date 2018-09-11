#ifndef NIXIE_QUATERNION_H_
#define NIXIE_QUATERNION_H_

#include "mathfu/quaternion.h"


namespace Nixie
{
	template<class T>
	using Quaternion = mathfu::Quaternion<T>;
}

#endif