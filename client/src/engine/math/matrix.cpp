#include "../../stdafx.h"

#include "matrix.h"


namespace Nixie
{
	template<class T>
	Matrix3x3<T>::Matrix3x3()
	{

	}


	template<class T>
	Matrix3x3<T> Matrix3x3<T>::Identity()
	{
		return Matrix3x3<T>();
	}


	template<class T>
	Matrix4x3<T>::Matrix4x3()
	{

	}


	template<class T>
	Matrix4x3<T> Matrix4x3<T>::Identity()
	{
		return Matrix4x3<T>();
	}


	template<class T>
	Matrix4x4<T>::Matrix4x4()
	{

	}


	template<class T>
	Matrix4x4<T> Matrix4x4<T>::Identity()
	{
		return Matrix4x4<T>();
	}
}