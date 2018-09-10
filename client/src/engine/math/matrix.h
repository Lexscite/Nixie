#ifndef NIXIE_MATRIX_H_
#define NIXIE_MATRIX_H_

#pragma once

#include "math.h"

// Written using following links:
// https://github.com/OmarAflak/Matrix/blob/master/matrix.h
// https://github.com/c650/matrix/blob/master/matrix.hpp


namespace Nixie
{
	template<class T>
	class Matrix3x3
	{
	public:
		Matrix3x3();

		static Matrix3x3<T> Identity();
	};


	template<class T>
	class Matrix4x3
	{
	public:
		Matrix4x3();

		static Matrix4x3<T> Identity();
	};


	template<class T>
	class Matrix4x4
	{
	public:
		Matrix4x4();

		static Matrix4x4<T> Identity();
	};
}

#endif