#ifndef VOODOO_VECTOR_H_
#define VOODOO_VECTOR_H_

#include "mathfu/vector.h"

namespace voodoo
{
	template<class T>
	using Vector2 = mathfu::Vector<T, 2>;

	template<class T>
	using Vector3 = mathfu::Vector<T, 3>;

	template<class T>
	using Vector4 = mathfu::Vector<T, 4>;

	using Vector2f = mathfu::Vector<float, 2>;
	using Vector3f = mathfu::Vector<float, 3>;
	using Vector4f = mathfu::Vector<float, 4>;
}

#endif