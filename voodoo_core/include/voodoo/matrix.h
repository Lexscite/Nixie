#ifndef VOODOO_MATRIX_H_
#define VOODOO_MATRIX_H_

#include <mathfu/matrix.h>

namespace voodoo
{
	template<class T>
	using Matrix3x3 = mathfu::Matrix<T, 3>;

	template<class T>
	using Matrix4x3 = mathfu::Matrix<T, 4, 3>;

	template<class T>
	using Matrix4x4 = mathfu::Matrix<T, 4>;

	using Matrix3x3f = mathfu::Matrix<float, 3>;
	using Matrix4x3f = mathfu::Matrix<float, 4, 3>;
	using Matrix4x4f = mathfu::Matrix<float, 4>;
}

#endif