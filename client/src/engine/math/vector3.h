#ifndef NIXIE_VECTOR3_H_
#define NIXIE_VECTOR3_H_

#pragma once

#include "math.h"


namespace Nixie
{
	template<class T>
	class Vector3
	{
	public:
		Vector3() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
		Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
		Vector3(T* a) : x(a[0]), y(a[1]), z(a[2]) {}

		// Static constructors
		inline static Vector3<T> Up() { return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }
		inline static Vector3<T> Down() { return Vector3<T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0)); }
		inline static Vector3<T> Forward() { return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(1)); }
		inline static Vector3<T> Backward() { return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(-1)); }
		inline static Vector3<T> Right() { return Vector3<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(0)); }
		inline static Vector3<T> Left() { return Vector3<T>(static_cast<T>(-1), static_cast<T>(1), static_cast<T>(0)); }

		inline T GetMagnitude() { return sqrt<T>(x * x + y * y + z * z) }
		inline Vector3<T>& Normalize() { return static_cast<T>(1) / GetMagnitude(); }
		inline void Inverse() { x = -x; y = -y; z = -z; }

		inline static T DotProduct(const Vector3<T> v1, const Vector3<T> v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
		inline static Vector3<T> CrossProduct(const Vector3<T> v1, const Vector3<T> v2) { return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
		inline static T Distance(const Vector3& v1, const Vector3& v2) { return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z).GetMagnitude(); }

		static Vector3<T> Vector3<T>::Rotate(const Quaternion& q);

	public:
		T x, y, z;
	};


	template<class T>
	inline Vector3<T> operator+(const Vector3<T>& v, const T& s)
	{
		return Vector3<T>(v.x + s, v.y + s, v.z + s);
	}


	template<class T>
	inline Vector3<T> operator+(const T& s, const Vector3<T>& v)
	{
		return Vector3<T>(v.x + s, v.y + s, v.z + s);
	}


	template<class T>
	inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}


	template<class T>
	inline Vector3<T> operator-(const Vector3<T>& v, const T& s)
	{
		return Vector3<T>(v.x - s, v.y - s, v.z - s);
	}


	template<class T>
	inline Vector3<T> operator-(const T& s, const Vector3<T>& v)
	{
		return Vector3<T>(v.x - s, v.y - s, v.z - s);
	}


	template<class T>
	inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}


	template<class T>
	inline Vector3<T>& operator+=(Vector3<T>& lhs, const T& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}


	template<class T>
	inline Vector3<T>& operator+=(Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}


	template<class T>
	inline Vector3<T>& operator-=(Vector3<T>& lhs, const T& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}


	template<class T>
	inline Vector3<T>& operator-=(Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
}

#endif