#ifndef NIXIE_COLOR_H_
#define NIXIE_COLOR_H_

#pragma once


namespace Nixie
{
	class Vector3;

	class Color
	{
	public:
		Color();
		Color(float value);
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		Color(const Vector3& v);
		Color(const Vector3& v, float a);

		inline operator float*() const { return new float[4]{ r, g, b, a }; };

	private:
		float ClampValue(float value);

	public:
		float r, g, b, a;
	};
}

#endif