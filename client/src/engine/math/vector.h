#ifndef NIXIE_VECTOR_H_
#define NIXIE_VECTOR_H_

#pragma once


namespace Nixie
{
	class Quaternion;

	class Vector2
	{
	public:
		Vector2();
		Vector2(float value);
		Vector2(float x, float y);

		//inline float GetMagnitude();
		//inline Vector2& Normalize();

		inline Vector2& operator*=(float s);

	public:
		float x, y;
	};

	//inline float Vector2::GetMagnitude() { return sqrtf(x * x + y * y); }

	//inline Vector2& Vector2::Normalize() { return (*this *= Math::InvSqrtf(x * x + y * y)); }

	inline Vector2& Vector2::operator*=(float s)
	{
		x *= s;
		y *= s;

		return *this;
	}

	class Vector3
	{
	public:
		Vector3();
		Vector3(float value);
		Vector3(float x, float y, float z);
		
		static Vector3 Up() { return Vector3(0, 1, 0); }
		static Vector3 Down() { return Vector3(0, -1, 0); }
		static Vector3 Right() { return Vector3(1, 0, 0); }
		static Vector3 Left() { return Vector3(-1, 0, 0); }
		static Vector3 Forward() { return Vector3(0, 0, 1); }
		static Vector3 Backward() { return Vector3(0, 0, -1); }

		inline float GetMagnitude();
		inline Vector3& Normalize();
		Vector3 Rotate(Quaternion q);

		static float Dot(Vector3 v1, Vector3 v2);
		static Vector3 Cross(Vector3 v1, Vector3 v2);

		inline Vector3 operator+(const Vector3& v) const;
		inline Vector3 operator-(const Vector3& v) const;
		inline Vector3 operator-() const;
		inline Vector3 operator*(const Vector3& v) const;
		inline Vector3 operator*(float s) const;
		inline Vector3 operator/(float s) const;

		inline Vector3& operator+=(const Vector3& v);
		inline Vector3& operator-=(const Vector3& v);
		inline Vector3& operator*=(float s);

	public:
		float x, y, z;
	};

	inline float Vector3::GetMagnitude() { return sqrtf(x * x + y * y + z * z); }

	inline Vector3& Vector3::Normalize() { return (*this *= 1.0f / std::sqrtf(x * x + y * y + z * z)); }

	inline Vector3 Vector3::operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
	inline Vector3 Vector3::operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
	inline Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }
	inline Vector3 Vector3::operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
	inline Vector3 Vector3::operator*(float s) const { return Vector3(x * s, y * s, z * s); }
	inline Vector3 Vector3::operator/(float s) const { return Vector3(x / s, y / s, z / s); }

	inline Vector3 operator*(float s, const Vector3& v) { return Vector3(v.x * s, v.y * s, v.z * s); }

	inline Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	inline Vector3& Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}
}

#endif