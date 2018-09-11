#ifndef NIXIE_MATRIX_H_
#define NIXIE_MATRIX_H_

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include "mathfu/matrix.h"
#include <d3d11.h>


namespace Nixie
{
	template<class T>
	using Matrix3x3 = mathfu::Matrix<T, 3>;

	template<class T>
	using Matrix4x3 = mathfu::Matrix<T, 4, 3>;

	template<class T>
	using Matrix4x4 = mathfu::Matrix<T, 4>;
}

#endif