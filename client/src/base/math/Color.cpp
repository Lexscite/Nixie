#include "Color.h"

Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

Color::Color(int r, int g, int b)
{
	this->r = 1.0f / 255.0f * (float)clamp(r, 0, 255);
	this->g = 1.0f / 255.0f * (float)clamp(g, 0, 255);
	this->b = 1.0f / 255.0f * (float)clamp(b, 0, 255);
	this->a = 1.0f;
}

Color::Color(int r, int g, int b, int a)
{
	this->r = 1 / 255 * (float)clamp(r, 0, 255);
	this->g = 1 / 255 * (float)clamp(g, 0, 255);
	this->b = 1 / 255 * (float)clamp(b, 0, 255);
	this->a = 1 / 255 * (float)clamp(a, 0, 255);
}

Color::Color(float r, float g, float b)
{
	this->r = clamp(r, 0.0f, 1.0f);
	this->g = clamp(g, 0.0f, 1.0f);
	this->b = clamp(b, 0.0f, 1.0f);
	this->a = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = clamp(r, 0.0f, 1.0f);
	this->g = clamp(g, 0.0f, 1.0f);
	this->b = clamp(b, 0.0f, 1.0f);
	this->a = clamp(a, 0.0f, 1.0f);
}

Color::Color(IntVector3 vector)
{
	this->r = 1 / 255 * (float)clamp(vector.x, 0, 255);
	this->g = 1 / 255 * (float)clamp(vector.y, 0, 255);
	this->b = 1 / 255 * (float)clamp(vector.z, 0, 255);
	this->a = 1.0f;
}

Color::Color(IntVector4 vector)
{
	this->r = 1 / 255 * (float)clamp(vector.x, 0, 255);
	this->g = 1 / 255 * (float)clamp(vector.y, 0, 255);
	this->b = 1 / 255 * (float)clamp(vector.z, 0, 255);
	this->a = 1 / 255 * (float)clamp(vector.t, 0, 255);
}

Color::Color(Vector3 vector)
{
	this->r = clamp(vector.x, 0.0f, 1.0f);
	this->g = clamp(vector.y, 0.0f, 1.0f);
	this->b = clamp(vector.z, 0.0f, 1.0f);
	this->a = 1.0f;
}

Color::Color(Vector4 vector)
{
	this->r = clamp(vector.x, 0.0f, 1.0f);
	this->g = clamp(vector.y, 0.0f, 1.0f);
	this->b = clamp(vector.z, 0.0f, 1.0f);
	this->a = clamp(vector.t, 0.0f, 1.0f);
}